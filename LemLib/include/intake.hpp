#pragma once

#include <string>


extern int intake_speed;

struct AutoIntake {
  bool run;
  bool reverse;
};

class Intake {

private:
  bool allow_intake;


  static bool auto_run;
  static bool auto_wheels;
  static bool auto_reverse;

  static bool use_sorting;
  static int signature_id;

public:

  Intake();

  static void run_auto();
  static void run_auto_wheels();

  static void run();
  static void stop();
  static void reverse();
  static void run_wheels();

  static void set_team_alliance(std::string team);

  static void task();
  static void run_auto_reverse();

  static void run_time(int time);
  
};



extern Intake intake;