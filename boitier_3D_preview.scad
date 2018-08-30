use <footswitch.scad>;
use <angle_bracket.scad>;
use <USB_connector.scad>;
use <midi_connector.scad>;
include <boitier_modules.scad>

//the enclosure
union(){
    color("blue",alpha=0.2) translate([0,0,low_step_height]) low_top_3D();
    translate([0,0,high_step_height])  high_top_3D();

    translate([0,thickness,0]) rotate([90,0,0]) low_front_3D();
    color("green",alpha=0.5) translate([0,60+thickness,0]) rotate([90,0,0]) high_front_3D();
    color("green") translate([0,pb_size_y,0]) rotate([90,0,0]) rear_3D();

    color("red",alpha=0.5) translate([thickness,0,0]) rotate([0,-90,0]) left_3D();
    color("red",alpha=0.5) translate([pb_size_x,0,0]) rotate([0,-90,0]) right_3D();

    color("grey",alpha=0.5) translate([0,0,-thickness]) bottom_3D();
}

//angle bracket
%union()
{
    translate([pb_size_x/2-15.5,thickness,low_step_height]) rotate([180,0,0]) angle_bracket_double();
    translate([pb_size_x/2+15.5,thickness,low_step_height]) rotate([180,0,0]) angle_bracket_double();
    translate([pb_size_x/2-18,60,low_step_height]) rotate([90,0,0]) angle_bracket_double();
    translate([pb_size_x/2+18,60,low_step_height]) rotate([90,0,0]) angle_bracket_double();
    translate([pb_size_x/2-35,180-thickness,high_step_height]) rotate([90,0,0]) angle_bracket_simple();
    translate([pb_size_x/2+30,180-thickness,high_step_height]) rotate([90,0,0]) angle_bracket_double();

    translate([thickness,120+20,high_step_height])rotate([90,0,90]) angle_bracket_double();
    translate([pb_size_x-thickness,120+20,high_step_height]) rotate([90,0,-90]) angle_bracket_double();
    translate([thickness,120-15,high_step_height])rotate([90,0,90]) angle_bracket_double();
    translate([pb_size_x-thickness,120-15,high_step_height]) rotate([90,0,-90]) angle_bracket_double();

    translate([thickness,45,low_step_height])rotate([90,0,90]) angle_bracket_double();
    translate([pb_size_x-thickness,45,low_step_height])rotate([90,0,-90]) angle_bracket_double();

    translate([thickness+8,thickness,0]) rotate([0,0,180]) angle_bracket_simple();
    translate([pb_size_x-(thickness+8),thickness,0]) rotate([0,0,180]) angle_bracket_simple();

    translate([thickness+8,pb_size_y-thickness,0]) rotate([0,0,0]) angle_bracket_simple();
    translate([pb_size_x-(thickness+8),pb_size_y-thickness,0]) rotate([0,0,0]) angle_bracket_simple();

    translate([thickness,60+thickness,high_step_height-8]) rotate([0,-90,180]) angle_bracket_simple();
    translate([pb_size_x-thickness,60+thickness,high_step_height-8]) rotate([0,90,180]) angle_bracket_simple();

    translate([thickness,180-thickness,high_step_height-8]) rotate([0,+90,0]) angle_bracket_simple();
    translate([pb_size_x-thickness,180-thickness,high_step_height-8]) rotate([0,-90,0]) angle_bracket_simple();
}

//footswitch
%union(){
    translate([fs_side_dist,20,0]) rotate([0,0,90]) footswitch();
    translate([pb_size_x-fs_side_dist,20,0]) rotate([0,0,90]) footswitch();
    translate([fs_side_dist,60+20,high_step_height-low_step_height]) rotate([0,0,0]) footswitch();
    translate([pb_size_x-fs_side_dist,60+20,high_step_height-low_step_height]) rotate([0,0,90]) footswitch();
}

//connector
%translate([95,180-thickness,13]) rotate([90,0,0]) usb_connector();
%translate([35,180,13]) rotate([-90,34,0]) midi_connector();
%translate([58,180,13]) rotate([-90,34,0]) midi_connector();
