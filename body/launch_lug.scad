$fn = 250;

inner_diam = 10;
outer_diam = 13;
length = 5;

difference() {
    union() {
        cylinder(h=length, r=outer_diam/2);
        translate([0,-outer_diam/2,0])
        cube([outer_diam, outer_diam, length]);
    }
    translate([0,0,-1])
    cylinder(h=length + 2, r=inner_diam/2);
    translate([32,0,-1])
    cylinder(h=length + 2, r=25);
}