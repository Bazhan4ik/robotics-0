#include "pros/device.h"
#include "pros/apix.h"

#include "intake.hpp"
#include "config.hpp"
#include "pros/motors.h"



int intake_speed = 127;
int stop_after;
int intake_timer;

Intake intake;



struct AnalyzedRing {
  bool valid;
  bool faultyRing;
};
AnalyzedRing analyze_ring(pros::vision_object_s_t ring, int height) {
  pros:printf("height: %d \n", ring.height);

  AnalyzedRing result;
  result.valid = ring.height > height;
  result.faultyRing = ring.height < -10;

  return result;
}

bool Intake::use_sorting = false;
bool Intake::auto_run = false;
bool Intake::auto_wheels = false;
bool Intake::auto_reverse = false;
int Intake::signature_id = 0;

Intake::Intake() {
  pros::c::v5_device_e_t vision_sensor_connected = pros::c::registry_get_plugged_type(17);

  if(vision_sensor_connected) {
    use_sorting = true;
  }

};



void Intake::set_team_alliance(std::string team) {
  if(team == "red" || team == "skills") {
    signature_id = 2;
  } else if(team == "blue") {
    signature_id = RED_SIGNATURE;
  }
};

void Intake::run_auto_reverse() {
  auto_run = true;
  auto_reverse = true;
}
void Intake::run_auto() {
  auto_run = true;
}
void Intake::run() {
  intake_chain.move(intake_speed);
  run_wheels();
}
void Intake::run_wheels() {
  intake_stage1.move(-intake_speed);
};
void Intake::run_auto_wheels() {
  auto_wheels = true;
};
void Intake::stop() {
  intake_chain.brake();
  intake_stage1.brake();
  auto_run = false;
  auto_reverse = false;
  auto_wheels = false;
}
void Intake::reverse() {
  intake_chain.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  intake_chain.move(-intake_speed);
  intake_stage1.move(intake_speed);
}
void Intake::run_time(int time) {
  auto_run = true;
  stop_after = time;
  intake_timer = pros::millis();
}

void Intake::task() {
  bool throw_ring = false;

  int ring_not_seen = 0;

  optical_sensor.set_integration_time(20);
  optical_sensor.set_led_pwm(100);

  while(true) {
    pros::delay(15);

    if(auto_wheels) {
      Intake::run_wheels();
      continue;
    }

    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) || auto_run) {
      if(stop_after && intake_timer + stop_after < pros::millis()) {
        Intake::stop();
        continue;
      }
      if(auto_reverse) {
        Intake::reverse();
        continue;
      }
      Intake::run();

      double hue = optical_sensor.get_hue();
      int proximity = optical_sensor.get_proximity();

      master.set_text(1, 1, "SENSOR: " + std::to_string(optical_sensor.get_hue()) + "     ");
      // master.set_text(1, 1, "SENSOR: " + std::to_string(hue));

      

      if(false && proximity > 200 && hue > 330.0 && hue < 370.0) {
        pros::delay(30);
        // master.set_text(1, 1, "+++ SENSOR: " + std::to_string(optical_sensor.get_hue()) + "    ");
        intake_chain.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        intake_chain.brake();
        pros::delay(200);
        intake_chain.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      }

    } else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) || auto_reverse) {
      Intake::reverse();
    } else {
      Intake::stop();
    }
  }
}