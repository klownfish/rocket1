inner_diam = 49.5;

hole_size = 15.5;

$fn = 250;


difference() {
    cylinder(h=2, r = inner_diam / 2);
    translate([0,0,-1])
    cylinder(h=4, r = hole_size / 2);
}