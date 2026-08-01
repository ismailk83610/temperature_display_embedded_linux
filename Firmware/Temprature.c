#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <time.h>

#define I2C_DEVICE "/dev/i2c-1"
#define SENSOR_ADDRESS 0x48
#define TEMPERATURE_REGISTER 0x00

int main(void)
{
    int i2c_file;
    uint8_t register_address = TEMPERATURE_REGISTER;
    uint8_t data[2];

    /* Open the Linux I2C device file */
    i2c_file = open(I2C_DEVICE, O_RDWR);

    if (i2c_file < 0) {
        perror("Failed to open I2C device");
        return EXIT_FAILURE;
    }

    /* Select the sensor using its I2C address */
    if (ioctl(i2c_file, I2C_SLAVE, SENSOR_ADDRESS) < 0) {
        perror("Failed to select I2C sensor");
        close(i2c_file);
        return EXIT_FAILURE;
    }

    printf("Temperature monitoring started\n");

    while (1) {
        /*
         * Tell the sensor that we want to read
         * its temperature register.
         */
        if (write(i2c_file, &register_address, 1) != 1) {
            perror("Failed to select temperature register");
            break;
        }

        /* Read two bytes from the sensor */
        if (read(i2c_file, data, 2) != 2) {
            perror("Failed to read temperature");
            break;
        }

        /*
         * TMP102 provides a 12-bit temperature value.
         * Combine the two received bytes.
         */
        int16_t raw_value =
            (int16_t)((data[0] << 8) | data[1]);

        raw_value >>= 4;

        /* Sign extension for negative temperatures */
        if (raw_value & 0x0800) {
            raw_value |= 0xF000;
        }

        float temperature = raw_value * 0.0625f;

        /* Get the current date and time */
        time_t current_time = time(NULL);
        struct tm *time_info = localtime(&current_time);

        char time_text[32];

        strftime(
            time_text,
            sizeof(time_text),
            "%Y-%m-%d %H:%M:%S",
            time_info
        );

        printf(
            "%s | Temperature: %.2f °C\n",
            time_text,
            temperature
        );

        /* Save the measurement in a log file */
        FILE *log_file =
            fopen("temperature_log.txt", "a");

        if (log_file != NULL) {
            fprintf(
                log_file,
                "%s | Temperature: %.2f °C\n",
                time_text,
                temperature
            );

            fclose(log_file);
        } else {
            perror("Failed to open log file");
        }

        /* Wait for two seconds */
        sleep(2);
    }

    close(i2c_file);

    return EXIT_SUCCESS;
}
