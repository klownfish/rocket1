use <M2.scad>
$fn = 250;


inner_diam = 49.5;
engine_size = 18.75;

difference() {
    union() {
            
        // main tube
        difference() {
            cylinder(h=65, r=engine_size/2 + 1);
            translate([0,0,-1])
            cylinder(h=67, r=engine_size/2);
            
            cube([100,8,90], center=true);
            cube([8,100,90], center=true);
            
            translate([0,100,45])
            rotate([90,0,0])
            cylinder(h=500, r=4);
            
            translate([-100,0,45])
            rotate([90,0,90])
            cylinder(h=500, r=4);
        }

        //upper holder
        translate([0,0,65])
        union() {
            difference() {
                union() {
                    cylinder(h=1,r=inner_diam/2);
                }
                translate([0,0,-1])
                cylinder(h=4,r=engine_size/2);
            }
            
            
            holders = 16;
            for (i = [1:1:holders]) {
                rotate([0,0,360/holders * i])
                translate([engine_size/2 + 0.05,0,0])
                rotate([-90,0,0])
                translate([0,0,-0.5])
                linear_extrude(1)
                polygon(points = [[0,0], [(inner_diam - engine_size) / 2 - 0.1, 0], [0, (inner_diam - engine_size) / 2 - 0.1]]);
            }
        }

        //lower holder
        difference() {
            cylinder(h=2, r=inner_diam/2);
            translate([0,0,-1])
            cylinder(h=4, r=engine_size/2);
        }
    }
    
    //engine screws
    translate([engine_size/2 + 2.1,0,-1])
    cylinder(h=10, r=1.2);
    translate([engine_size/2 + 2.1,0,2.75])
    rotate([0, 0, 90])
    NutM2();

    translate([-engine_size/2 - 2.1,0,-1])
    cylinder(h=10, r=1.2);
    translate([-engine_size/2 - 2.1,0,2.75])
    rotate([0, 0, 90])
    NutM2();
}