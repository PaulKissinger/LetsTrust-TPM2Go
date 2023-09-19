/**
  * @brief              LetsTrust-TPM2Go reset handler
  * @details            ltt2g_rst.c implements a basic method to reset the TPM on a LetsTrust-TPM2Go.
  * @file               ltt2g_rst.c
  * @date               2023/09/19
  * @copyright  MIT.\n
  * \n
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */

#include "ltt2g_rst.h"


/**
  * @brief                                      Main entry point of the application.
  * @details                                    Handles the command line input and starts the communication with the TPM.
  * @param      [in]    argc                    Counter for input parameters.
  * @param      [in]    **argv                  Input parameters.
  * @return     One of the listed return codes, the TPM return code or the error code stored in the global errno system variable.
  * @retval     EXIT_SUCCESS                    In case of success.
  * @retval     ERR_BAD_CMD                     In case an invalid command line option.
  */
int main(int argc, char **argv){

        // ---------- Local declarations ----------
        int ret_val = EXIT_SUCCESS;             // Return value.
        int i = 0;                              // Command line parsing counter.
        int option = 0;                         // Command line option.
        int option_index = 0;
        int pinValue = 0;

        static struct option long_options[] = {
            {"cycle", no_argument,       0, 'c' },
            {"level", required_argument, 0, 'l' },
            {"help",  no_argument,       0, 'h' },
            {0,       0,                 0, 0   }
        };

        libusb_device_handle *dev_handle = NULL;
        libusb_context *ctx = NULL;

        ret_val = libusb_init (&ctx);
        if(ret_val){
                fprintf(stderr, "libusb init failed.");
        }

        dev_handle = libusb_open_device_with_vid_pid (ctx, VID_PI3G, PID_LTT2GO);
        if(dev_handle == NULL){
                fprintf(stderr, "LetsTrust-TPM2Go not found.");
        }

        // --- program --
        printf("\n");

        // begin of DO WHILE(FALSE) for error handling.
        do{
                // --- check for command line param ---
                if (1 == argc){
                        fprintf(stderr, "LTT2G_RST needs an option. Use '-h' for displaying help.\n");
                        ret_val = ERR_BAD_CMD;
                        break;
                }

                // --- command line parsing with getopt_long() ---
                opterr = 0; // Disable getopt_long error messages in case of unknown parameters; use own error messages.

                // loop through parameters with getopt_long.
                while (-1 != (option = getopt_long(argc, argv, "chl:", long_options, &option_index))){
                        switch (option){
                                case 'c': //Cycle the rst by set low and high with 500ms delay
                                        //set low
                                        ret_val = LtTpm2Go_SetGpioValue(dev_handle, LTTPM2GO_RST_PIN, LTTPM2GO_RST_LOGIC_LEVEL_LOW);
                                        RET_VAL_CHECK(ret_val);
                                        //wait
                                        usleep(500000);
                                        //set high
                                        ret_val = LtTpm2Go_SetGpioValue(dev_handle, LTTPM2GO_RST_PIN, LTTPM2GO_RST_LOGIC_LEVEL_HIGH);
                                        RET_VAL_CHECK(ret_val);
                                        fprintf(stderr, "Reset of the TPM is cycled, please perform a TPM startup\n");
                                        break;
                                case 'l':  //set rst to given level
                                        if (0 == strcmp("high", optarg)){
                                                pinValue = 1;
                                        }
                                        else if (0 == strcmp("low", optarg)){
                                                pinValue = 0;
                                        }
                                        else{
                                                fprintf(stderr, "-l --level need an parameter \"high\" or \"low\". Use '-h' for the help.\n");
                                                break;
                                        }
                                        ret_val = LtTpm2Go_SetGpioValue(dev_handle, LTTPM2GO_RST_PIN, pinValue);
                                        RET_VAL_CHECK(ret_val);
                                        usleep(250000);
                                        fprintf(stderr, "Reset of the TPM was set to %s, TPM should %s answer on requests\n", (0 != pinValue ? "high" : "low"), (0 != pinValue? "now" : "not"));
                                        break;
                                case 'h': // print help
                                        print_info();
                                        ret_val = EXIT_SUCCESS;
                                        break;
                                default:
                                        if('l' == optopt){
                                                fprintf(stderr, "-l --level need an parameter \"high\" or \"low\". Use '-h' for help.\n");
                                                ret_val = ERR_BAD_CMD;

                                        }
                                        else if(isprint(optopt)){
                                                // Unknown parameter.
                                                fprintf(stderr, "Unknown option '-%c'. Use '-h' for help.\n", optopt);
                                                ret_val = ERR_BAD_CMD;
                                        }
                                        else{
                                                // Non-printable character.
                                                fprintf(stderr, "Invalid command line character. Use '-h' for help.\n");
                                                ret_val = ERR_BAD_CMD;
                                        }
                                        break;
                        } // end of switch.


                } // end of while (command line param parsing loop).

                // If no error has occurred, handle remaining unknown params, if present.
                RET_VAL_CHECK(ret_val); // If we do not check and break here in case of an error, we would override the previous error
                for (i = optind; i < argc; i++){
                        ret_val = ERR_BAD_CMD;
                        fprintf(stderr, "Non-option argument '%s'. Use '-h' for help.\n", argv[i]);
                        break;
                }
        } while (0); // End of DO WHILE FALSE loop.

        printf("\n");
        // Release the interface
        libusb_release_interface(dev_handle, 0);
        return ret_val;
}

static int LtTpm2Go_SetGpioValue(libusb_device_handle *devHandle, const int gpioNumber, const int value){

        // ---------- Local declarations ----------
        int length = 0;
        int lValue = 0; // local value
        unsigned char buffer[1];
        int rStatus = EXIT_SUCCESS;
        int ioTimeout = 5000;

        if(devHandle == NULL){
                return ERR_BAD_CMD;
        };
        //limit the value to 1
        if(0 != value){
                lValue = 1;
        }

        rStatus = libusb_control_transfer(devHandle, CY_VENDOR_REQUEST_DEVICE_TO_HOST, CY_GPIO_SET_VALUE_CMD,
                        gpioNumber, lValue, buffer, length, ioTimeout);

        if(rStatus >= 0){
                return EXIT_SUCCESS;
        }
        else if(rStatus == LIBUSB_ERROR_TIMEOUT){
                return LIBUSB_ERROR_TIMEOUT;
        }
        else {
                return ERR_BAD_CMD;
        }
}

static void print_info()
{
        printf("'-c' --cycle : cycle the reset line of the TPM \n");
        printf("'-l' --level [option] : set the reset line of the TPM to high or low [\"high\",\"low\"]\n");
        printf("'-h' --help : print this help\n");
}
