#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#define _CRT_SECURE_NO_WARNINGS

#include  "OscDual_lib.h"
#define BOARD_IP_ADDRESS "192.168.50.150"

#define FILE_PATH "c:\\temp"
#define FILE_NAME "data"


void writeFile(uint32_t *data, int e, int ch_group) {
	FILE *fp;
	char filename[1024];
	sprintf_s(filename, 1024, "%s\\%s_%d_%d.txt", FILE_PATH, FILE_NAME, ch_group, e);
	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Unable to open file %s for writing...", filename);
		exit(0);
	}
	fprintf(fp, "     #\t");
	for (int i = 0; i < 4; i++)
		fprintf(fp, "  CH%02d\t", i);
	fprintf(fp, "\n");

	for (int j = 0; j < 16384; j++) {
		fprintf(fp, "%6d\t", j);
		for (int i = 0; i < 4; i++)
			fprintf(fp, "%6d\t", data[i * 16384 + j]);
		fprintf(fp, "\n");
	}
	fclose(fp);
}

int main(int argc, char* argv[])
{
	NI_HANDLE handle;
	int ret;
	uint32_t    val;


	R_Init();

	
	uint32_t status_osc = 0;
	uint32_t *data_osc;
	uint32_t read_data_osc;
	uint32_t valid_data_osc;
	int32_t position = 0;
	int32_t decimator = 0;
	int32_t pre_trigger = 300;
	int32_t software_trigger = 1;
	int32_t analog_trigger = 0;
	int32_t digital0_trigger = 0;
	int32_t digital1_trigger = 0;
	int32_t digital2_trigger = 0;
	int32_t digital3_trigger = 0;
	int32_t trigger_channel = 3;
	int32_t trigger_edge = 0;
	int32_t trigger_level = 10000;
	int32_t timeout_osc = 1000;
	int32_t size_osc = 16384 * 4;
	uint32_t *read_analog;
	uint32_t *read_digital0;
	uint32_t *read_digital1;
	uint32_t *read_digital2;
	uint32_t *read_digital3;

	data_osc = (uint32_t *)malloc(size_osc * sizeof(uint32_t));
	read_analog = (uint32_t *)malloc(size_osc * sizeof(uint32_t));
	read_digital0 = (uint32_t *)malloc(size_osc * sizeof(uint32_t));
	read_digital1 = (uint32_t *)malloc(size_osc * sizeof(uint32_t));
	read_digital2 = (uint32_t *)malloc(size_osc * sizeof(uint32_t));
	read_digital3 = (uint32_t *)malloc(size_osc * sizeof(uint32_t));


	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { printf("Unable to connect to the board!\n"); return (-1); };
#ifndef CUSTOM_EXAMPLE		
	

	int Osc_Events = 100;
	int e = 0;
	printf("\n\nStarting acquisition\n\n");

	if (OSCILLOSCOPE_Oscilloscope_0_SET_PARAMETERS(decimator, pre_trigger, software_trigger, analog_trigger, digital0_trigger, digital1_trigger,
		digital2_trigger, digital3_trigger, trigger_channel, trigger_edge, trigger_level, &handle) != 0) printf("Set Parameters Error");
	if (OSCILLOSCOPE_Oscilloscope_1_SET_PARAMETERS(decimator, pre_trigger, software_trigger, analog_trigger, digital0_trigger, digital1_trigger,
		digital2_trigger, digital3_trigger, trigger_channel, trigger_edge, trigger_level, &handle) != 0) printf("Set Parameters Error");
	if (OSCILLOSCOPE_Oscilloscope_2_SET_PARAMETERS(decimator, pre_trigger, software_trigger, analog_trigger, digital0_trigger, digital1_trigger,
		digital2_trigger, digital3_trigger, trigger_channel, trigger_edge, trigger_level, &handle) != 0) printf("Set Parameters Error");
	if (OSCILLOSCOPE_Oscilloscope_3_SET_PARAMETERS(decimator, pre_trigger, software_trigger, analog_trigger, digital0_trigger, digital1_trigger,
		digital2_trigger, digital3_trigger, trigger_channel, trigger_edge, trigger_level, &handle) != 0) printf("Set Parameters Error");
	if (OSCILLOSCOPE_Oscilloscope_4_SET_PARAMETERS(decimator, pre_trigger, software_trigger, analog_trigger, digital0_trigger, digital1_trigger,
		digital2_trigger, digital3_trigger, trigger_channel, trigger_edge, trigger_level, &handle) != 0) printf("Set Parameters Error");
	if (OSCILLOSCOPE_Oscilloscope_5_SET_PARAMETERS(decimator, pre_trigger, software_trigger, analog_trigger, digital0_trigger, digital1_trigger,
		digital2_trigger, digital3_trigger, trigger_channel, trigger_edge, trigger_level, &handle) != 0) printf("Set Parameters Error");
	if (OSCILLOSCOPE_Oscilloscope_6_SET_PARAMETERS(decimator, pre_trigger, software_trigger, analog_trigger, digital0_trigger, digital1_trigger,
		digital2_trigger, digital3_trigger, trigger_channel, trigger_edge, trigger_level, &handle) != 0) printf("Set Parameters Error");
	if (OSCILLOSCOPE_Oscilloscope_7_SET_PARAMETERS(decimator, pre_trigger, software_trigger, analog_trigger, digital0_trigger, digital1_trigger,
		digital2_trigger, digital3_trigger, trigger_channel, trigger_edge, trigger_level, &handle) != 0) printf("Set Parameters Error");

	
	if (OSCILLOSCOPE_Oscilloscope_0_START(&handle) != 0) printf("Start Error");
	if (OSCILLOSCOPE_Oscilloscope_1_START(&handle) != 0) printf("Start Error");
	if (OSCILLOSCOPE_Oscilloscope_2_START(&handle) != 0) printf("Start Error");
	if (OSCILLOSCOPE_Oscilloscope_3_START(&handle) != 0) printf("Start Error");
	if (OSCILLOSCOPE_Oscilloscope_4_START(&handle) != 0) printf("Start Error");
	if (OSCILLOSCOPE_Oscilloscope_5_START(&handle) != 0) printf("Start Error");
	if (OSCILLOSCOPE_Oscilloscope_6_START(&handle) != 0) printf("Start Error");
	if (OSCILLOSCOPE_Oscilloscope_7_START(&handle) != 0) printf("Start Error");


	while (e<Osc_Events)
	{

		if (OSCILLOSCOPE_Oscilloscope_0_STATUS(&status_osc, &handle) != 0) printf("Status Error");
		if (status_osc == 1) {
			memset(data_osc, 0, size_osc);
			if (OSCILLOSCOPE_Oscilloscope_0_POSITION(&position, &handle) != 0) printf("Position Error");
			if (OSCILLOSCOPE_Oscilloscope_0_DOWNLOAD(data_osc, size_osc / 2, timeout_osc, &handle, &read_data_osc, &valid_data_osc) != 0) printf("Get Data Error");
			if (OSCILLOSCOPE_Oscilloscope_0_RECONSTRUCT(data_osc, position, pre_trigger, read_analog, read_digital0, read_digital1, read_digital2, read_digital3) != 0) printf("Reconstruction Error");
			writeFile(read_analog, e, 0);
			if (OSCILLOSCOPE_Oscilloscope_0_START(&handle) != 0) printf("Start Error");
		}

		if (OSCILLOSCOPE_Oscilloscope_1_STATUS(&status_osc, &handle) != 0) printf("Status Error");
		if (status_osc == 1) {
			memset(data_osc, 0, size_osc);
			if (OSCILLOSCOPE_Oscilloscope_1_POSITION(&position, &handle) != 0) printf("Position Error");
			if (OSCILLOSCOPE_Oscilloscope_1_DOWNLOAD(data_osc, size_osc / 2, timeout_osc, &handle, &read_data_osc, &valid_data_osc) != 0) printf("Get Data Error");
			if (OSCILLOSCOPE_Oscilloscope_1_RECONSTRUCT(data_osc, position, pre_trigger, read_analog, read_digital0, read_digital1, read_digital2, read_digital3) != 0) printf("Reconstruction Error");
			writeFile(read_analog, e, 1);
			if (OSCILLOSCOPE_Oscilloscope_1_START(&handle) != 0) printf("Start Error");
		}

		if (OSCILLOSCOPE_Oscilloscope_2_STATUS(&status_osc, &handle) != 0) printf("Status Error");
		if (status_osc == 1) {
			memset(data_osc, 0, size_osc);
			if (OSCILLOSCOPE_Oscilloscope_2_POSITION(&position, &handle) != 0) printf("Position Error");
			if (OSCILLOSCOPE_Oscilloscope_2_DOWNLOAD(data_osc, size_osc / 2, timeout_osc, &handle, &read_data_osc, &valid_data_osc) != 0) printf("Get Data Error");
			if (OSCILLOSCOPE_Oscilloscope_2_RECONSTRUCT(data_osc, position, pre_trigger, read_analog, read_digital0, read_digital1, read_digital2, read_digital3) != 0) printf("Reconstruction Error");
			writeFile(read_analog, e, 2);
			if (OSCILLOSCOPE_Oscilloscope_2_START(&handle) != 0) printf("Start Error");
		}
		
		if (OSCILLOSCOPE_Oscilloscope_3_STATUS(&status_osc, &handle) != 0) printf("Status Error");
		if (status_osc == 1) {
			memset(data_osc, 0, size_osc);
			if (OSCILLOSCOPE_Oscilloscope_3_POSITION(&position, &handle) != 0) printf("Position Error");
			if (OSCILLOSCOPE_Oscilloscope_3_DOWNLOAD(data_osc, size_osc / 2, timeout_osc, &handle, &read_data_osc, &valid_data_osc) != 0) printf("Get Data Error");
			if (OSCILLOSCOPE_Oscilloscope_3_RECONSTRUCT(data_osc, position, pre_trigger, read_analog, read_digital0, read_digital1, read_digital2, read_digital3) != 0) printf("Reconstruction Error");
			writeFile(read_analog, e, 3);
			if (OSCILLOSCOPE_Oscilloscope_3_START(&handle) != 0) printf("Start Error");
		}

		if (OSCILLOSCOPE_Oscilloscope_4_STATUS(&status_osc, &handle) != 0) printf("Status Error");
		if (status_osc == 1) {
			memset(data_osc, 0, size_osc);
			if (OSCILLOSCOPE_Oscilloscope_4_POSITION(&position, &handle) != 0) printf("Position Error");
			if (OSCILLOSCOPE_Oscilloscope_4_DOWNLOAD(data_osc, size_osc / 2, timeout_osc, &handle, &read_data_osc, &valid_data_osc) != 0) printf("Get Data Error");
			if (OSCILLOSCOPE_Oscilloscope_4_RECONSTRUCT(data_osc, position, pre_trigger, read_analog, read_digital0, read_digital1, read_digital2, read_digital3) != 0) printf("Reconstruction Error");
			writeFile(read_analog, e, 4);
			if (OSCILLOSCOPE_Oscilloscope_4_START(&handle) != 0) printf("Start Error");
		}

		if (OSCILLOSCOPE_Oscilloscope_5_STATUS(&status_osc, &handle) != 0) printf("Status Error");
		if (status_osc == 1) {
			memset(data_osc, 0, size_osc);
			if (OSCILLOSCOPE_Oscilloscope_5_POSITION(&position, &handle) != 0) printf("Position Error");
			if (OSCILLOSCOPE_Oscilloscope_5_DOWNLOAD(data_osc, size_osc / 2, timeout_osc, &handle, &read_data_osc, &valid_data_osc) != 0) printf("Get Data Error");
			if (OSCILLOSCOPE_Oscilloscope_5_RECONSTRUCT(data_osc, position, pre_trigger, read_analog, read_digital0, read_digital1, read_digital2, read_digital3) != 0) printf("Reconstruction Error");
			writeFile(read_analog, e, 5);
			if (OSCILLOSCOPE_Oscilloscope_5_START(&handle) != 0) printf("Start Error");
		}

		if (OSCILLOSCOPE_Oscilloscope_6_STATUS(&status_osc, &handle) != 0) printf("Status Error");
		if (status_osc == 1) {
			memset(data_osc, 0, size_osc);
			if (OSCILLOSCOPE_Oscilloscope_6_POSITION(&position, &handle) != 0) printf("Position Error");
			if (OSCILLOSCOPE_Oscilloscope_6_DOWNLOAD(data_osc, size_osc / 2, timeout_osc, &handle, &read_data_osc, &valid_data_osc) != 0) printf("Get Data Error");
			if (OSCILLOSCOPE_Oscilloscope_6_RECONSTRUCT(data_osc, position, pre_trigger, read_analog, read_digital0, read_digital1, read_digital2, read_digital3) != 0) printf("Reconstruction Error");
			writeFile(read_analog, e, 6);
			if (OSCILLOSCOPE_Oscilloscope_6_START(&handle) != 0) printf("Start Error");
		}

		if (OSCILLOSCOPE_Oscilloscope_7_STATUS(&status_osc, &handle) != 0) printf("Status Error");
		if (status_osc == 1) {
			memset(data_osc, 0, size_osc);
			if (OSCILLOSCOPE_Oscilloscope_7_POSITION(&position, &handle) != 0) printf("Position Error");
			if (OSCILLOSCOPE_Oscilloscope_7_DOWNLOAD(data_osc, size_osc / 2, timeout_osc, &handle, &read_data_osc, &valid_data_osc) != 0) printf("Get Data Error");
			if (OSCILLOSCOPE_Oscilloscope_7_RECONSTRUCT(data_osc, position, pre_trigger, read_analog, read_digital0, read_digital1, read_digital2, read_digital3) != 0) printf("Reconstruction Error");
			writeFile(read_analog, e, 7);
			if (OSCILLOSCOPE_Oscilloscope_7_START(&handle) != 0) printf("Start Error");
		}
		e++;
		printf("%6d/%6d\r", e, Osc_Events);
		fflush(stdout);
	}
	printf("\n\nDownload Finished\n\n");
	
#else

#endif

	return 0;
}

 