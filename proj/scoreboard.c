#include "scoreboard.h"

/**
 * @file scoreboard.c
 * @brief This file contains the implementation of the scoreboard
 */


/** @name Global variables */
///@{
int record_points[5] = {-1, -1, -1, -1, -1};
///@}


/** @name Static variables */
///@{
static char record_names[5][11] = {"", "", "", "", ""};
static int record_days[5] = {0, 0, 0, 0, 0};
static int record_months[5] = {0, 0, 0, 0, 0};
static int record_years[5] = {0, 0, 0, 0, 0};
static int record_hours[5] = {0, 0, 0, 0, 0};
static int record_minutes[5] = {0, 0, 0, 0, 0};
///@}


void register_score(int points, char *name, int day, int month, int year, int hours, int minutes) {

  for (int i = 0; i < 5; i++) {
    
    if (points > record_points[i]) {

      int tmp_points = record_points[i];
      char tmp_name[11];
      strcpy(tmp_name, record_names[i]);
      int tmp_day = record_days[i];
      int tmp_month = record_months[i];
      int tmp_year = record_years[i];
      int tmp_hours = record_hours[i];
      int tmp_minutes = record_minutes[i];

      record_points[i] = points;
      strcpy(record_names[i], name);
      record_days[i] = day;
      record_months[i] = month;
      record_years[i] = year;
      record_hours[i] = hours;
      record_minutes[i] = minutes;

      if (tmp_points == -1)
        break;

      points = tmp_points;
      strcpy(name, tmp_name);
      day = tmp_day;
      month = tmp_month;
      year = tmp_year;
      hours = tmp_hours;
      minutes = tmp_minutes;

    }
  }

  write_scores_to_file();
}

char* itoa(int val){

  if (val == 0) return "0";

	static char buf[32] = {0};
	int i = 30;
	
	for(; val && i ; --i, val /= 10)
		buf[i] = "0123456789abcdef"[val % 10];
	
	return &buf[i+1];	
}


int stringToInt(char* val) {

  int res = 0;
  for (int i = 0; (val[i] != '\0') && (val[i] != '\n'); i++) {

    if ((val[i] > 47) && (val[i] < 58)) {
      res *= 10;
      res += (val[i] - 48);
    }

  }

  return res;
}

void write_top5_in_the_screen() {

  int y = 200;

  for (int i = 0; i < 5; i++) {

    if (record_points[i] == -1)
      break;

    draw_word_centralized(record_names[i], 93, 353, y);
    draw_number_centralized(record_points[i], 351, 441, y);

    char time_string[17] = {0};

    if (record_days[i] < 10) {
      strcat(time_string, "0");
    }
    strcat(time_string, itoa(record_days[i]));
    strcat(time_string, "/");

    if (record_months[i] < 10) {
      strcat(time_string, "0");
    }
    strcat(time_string, itoa(record_months[i]));
    strcat(time_string, "/");

    if (record_years[i] < 10) {
      strcat(time_string, "0");
    } 
    strcat(time_string, itoa(record_years[i]));

    strcat(time_string, " - ");

    if (record_hours[i] < 10) {
      strcat(time_string, "0");
    }
    strcat(time_string, itoa(record_hours[i]));
    strcat(time_string, ":");
    
    if (record_minutes[i] < 10) {
      strcat(time_string, "0");
    }
    strcat(time_string, itoa(record_minutes[i]));
    time_string[16] = '\0';

    draw_word_centralized(time_string, 454, 699, y);

    y += 33;
  }
}

void write_scores_to_file() {

  FILE *fileScoresRegister;
  fileScoresRegister = fopen("/home/lcom/labs/proj/scoresRegister.txt", "w");

  for (int i = 0; (i < 5) && (record_points[i] != -1); i++) {

    if (i != 0) fprintf(fileScoresRegister, "\n");
    fprintf(fileScoresRegister, "%s ", itoa(record_points[i]));
    fprintf(fileScoresRegister, "%s ", record_names[i]);
    fprintf(fileScoresRegister, "%s ", itoa(record_days[i]));
    fprintf(fileScoresRegister, "%s ", itoa(record_months[i]));
    fprintf(fileScoresRegister, "%s ", itoa(record_years[i]));
    fprintf(fileScoresRegister, "%s ", itoa(record_hours[i]));
    fprintf(fileScoresRegister, "%s", itoa(record_minutes[i]));

  }

  fclose(fileScoresRegister);

}

void read_scores_from_file() {

  FILE *fileScoresRegister;
  fileScoresRegister = fopen("/home/lcom/labs/proj/scoresRegister.txt", "r");

  //If file doesnt exist yet
  if (fileScoresRegister == NULL)
    return;

  for (int i = 0; (i < 5) && !feof(fileScoresRegister); i++) {

    char scoreContent[50] = {0};
    fgets(scoreContent, 150, fileScoresRegister);

    if (strncmp(scoreContent, "\0", 1) == 0) break;

    char *ptr = strtok(scoreContent, " ");
    record_points[i] = stringToInt(ptr);
    ptr = strtok(NULL, " ");
    strcpy(record_names[i], ptr);
    ptr = strtok(NULL, " ");
    record_days[i] = stringToInt(ptr);
    ptr = strtok(NULL, " ");
    record_months[i] = stringToInt(ptr);
    ptr = strtok(NULL, " ");
    record_years[i] = stringToInt(ptr);
    ptr = strtok(NULL, " ");
    record_hours[i] = stringToInt(ptr);
    ptr = strtok(NULL, " ");
    record_minutes[i] = stringToInt(ptr);

  }

  fclose(fileScoresRegister);
}
