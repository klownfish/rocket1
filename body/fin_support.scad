$fn = 250;
height = 20;
difference() {
    for(i = [0: 3]) {
        rotate([0,0,120 * i])
        translate([0,0,0])
        difference () {
            translate([0, -2,0])
            cube([59, 4, height]);
            translate([0, -0.8,2])
            cube([60, 2, height + 1]);
        }
    }
    
    translate([0,0,2])
    cylinder(r=30, h = 82);
}