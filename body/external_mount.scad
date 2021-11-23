$fn = 250;


hole1 = [4.57, 0, 2.54];
hole2 = [4.57, 0, 97-2.54];
hole3 = [36-4.57, 0, 2.54];
hole4 = [36-4.57, 0, 97-2.54];

fc_x = 36;
fc_z = 98;
fc_margin = 2;

wall_width = 2;

module holes() {
    difference() {
        union () {
            cube([36 + fc_margin * 2, wall_width, 100 +  fc_margin * 2]);
            
            translate([0 + fc_margin,wall_width + 3,0 + fc_margin])
            union() {
                translate(hole1)
                rotate([90,0,0])
                cylinder(h=3, r=2);
                
                translate(hole2)
                rotate([90,0,0])
                cylinder(h=3, r=2);
                
                translate(hole3)
                rotate([90,0,0])
                cylinder(h=3, r=2);
                
                translate(hole4)
                rotate([90,0,0])
                cylinder(h=3, r=2);
            }
        }
        
        translate([0 + fc_margin,10,0 + fc_margin])
        union() {
            translate(hole1)
            rotate([90,0,0])
            cylinder(h=100, r=1.2);
            
            translate(hole2)
            rotate([90,0,0])
            cylinder(h=100, r=1.2);
            
            translate(hole3)
            rotate([90,0,0])
            cylinder(h=100, r=1.2);
            
            translate(hole4)
            rotate([90,0,0])
            cylinder(h=100, r=1.2);
        }
    };
}

module poles() {
    union() {
        union () {
            cube([36 + fc_margin * 2, wall_width, 100 +  fc_margin * 2]);
            
            translate([0 + fc_margin,wall_width + 3,0 + fc_margin])
            union() {
                translate(hole1)
                rotate([90,0,0])
                cylinder(h=3, r=2);
                
                translate(hole2)
                rotate([90,0,0])
                cylinder(h=3, r=2);
                
                translate(hole3)
                rotate([90,0,0])
                cylinder(h=3, r=2);
                
                translate(hole4)
                rotate([90,0,0])
                cylinder(h=3, r=2);
            }
        }
        
        translate([0 + fc_margin,10,0 + fc_margin])
        union() {
            translate(hole1)
            rotate([90,0,0])
            cylinder(h=8, r=1);
            
            translate(hole2)
            rotate([90,0,0])
            cylinder(h=8, r=1);
            
            translate(hole3)
            rotate([90,0,0])
            cylinder(h=8, r=1);
            
            translate(hole4)
            rotate([90,0,0])
            cylinder(h=8, r=1);
        }
    };
}

module hanger() {
    difference() {
        cube([36,30,1.3 + 6]);
        translate([-1,-1,3])
        cube([38,28, 1.3]);
    }
}

poles();
//translate([0,-40,0])
//hanger();

