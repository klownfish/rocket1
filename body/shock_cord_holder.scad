$fn = 250;

inner_diam = 49;
hole_size = 6;
size = 14;
height = 14;

difference() {
    intersection() {
        translate([0,0,-50])
        cylinder(h = 100, r = inner_diam/2);
        translate([inner_diam/2, 0, 0])
        union() {
            cylinder(h=height/2, r = size/2);
            sphere(r= size/2);
        }
    }
    translate([inner_diam/2, 0, -50])
    cylinder(h=100, r = hole_size/2);
}