$fn = 250;

inner_diam = 49;
length = 50;

difference() {
    cylinder(h=length, r=inner_diam/2);
    translate([0, 0, 252])
    cube([inner_diam + 5, inner_diam - 20, 500], center = true);
    translate([0, 0, 252])
    cube([inner_diam - 20, inner_diam + 5, 500], center = true);
    translate([0, 0, -1])
    cylinder(h=length+2, r=inner_diam/2 - 1);
}