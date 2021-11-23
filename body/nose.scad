use <M2.scad>;
use <M3.scad>;

screw_r = 1.2;
$fn = 250;

module cone_elliptical(n = 0.5, R = 5, L = 10, s = 500){
// ELLIPTICAL NOSE CONE:
//
// Formula: y = R * sqrt(1 - pow((x / L), 2));

echo(str("ELLIPTICAL NOSE CONE"));    
echo(str("n = ", n)); 
echo(str("R = ", R)); 
echo(str("L = ", L)); 
echo(str("s = ", s)); 

inc = 1/s;

rotate_extrude(convexity = 10, $fn = s)
for (i = [1 : s]){

    x_last = L * (i - 1) * inc;
    x = L * i * inc;

    y_last = R * sqrt(1 - pow((x_last/L), 2));
    y = R * sqrt(1 - pow((x/L), 2));

    rotate([0,0,90]) polygon(points = [[0, y_last], [0, y], [x, y], [x_last, y_last]], convexity = 10);
}
}

module flight_controller () {
    difference () {
        union () {
            cube([36, 10, 97]);
            translate([18-5,0,97])
            cube([10,10,60]);
        }
        
        translate([4.57, -1, 2.54])
        rotate([-90,0,0])
        cylinder(h=12, r=1);
        
        translate([4.57, -1, 97-2.54])
        rotate([-90,0,0])
        cylinder(h=12, r=1);
        
        translate([36-4.57, -1, 2.54])
        rotate([-90,0,0])
        cylinder(h=12, r=1);
        
        translate([36-4.57, -1, 97-2.54])
        rotate([-90,0,0])
        cylinder(h=12, r=1);
    }
};



module fc_mount_v2() {
    hole1 = [4.57, 0, 2.54];
    hole2 = [4.57, 0, 97-2.54];
    hole3 = [36-4.57, 0, 2.54];
    hole4 = [36-4.57, 0, 97-2.54];
    beam_width = 10;
    base_height = 1;
    extra_height = 5;
    outer_diam = 52.5;
    mount_offset = -16;
    beam_fatness = 2;
    nose_cone_inner_diam = 50;
    //rack
    translate([-18,mount_offset,base_height + extra_height])
    difference () {
        union () {
            translate([2,-3,-5])
            cube([9,5,11]);
            translate([25,-3,-5])
            cube([9,5,11]);
            
            //gps
            translate([13,-8, -5])
            cube([10,1,11]);
        }
        translate(hole1 - [0,10,0])
        rotate([-90,0,0])
        cylinder(h=52, r=screw_r);
        translate(hole1 - [0,3,0])
        rotate([90,90,0])
        NutM2();
        
        
        translate(hole3 - [0,10,0])
        rotate([-90,0,0])
        cylinder(h=52, r=screw_r);
        translate(hole3 - [0,3,0])
        rotate([90,90,0])
        NutM2();
        //GPS
        translate([7.75,-7,-5])
        cube([20.5,5,22]);
    }
    
    //camera holder
    translate([0,14,0])
    camera_mount();
    
    //nose holder
    intersection() {
        cylinder(h= 100, r=nose_cone_inner_diam/2);
        difference() {
            union() {
                translate([nose_cone_inner_diam / 2 - 4, -3,0])
                cube([4,6,7]);
                translate([-nose_cone_inner_diam / 2, -3, 0])
                cube([4,6,7]);
            }
            translate([nose_cone_inner_diam / 2 - 2.5, 0, 4])
            rotate([0,90,0])
            union() {
                NutM2();
                cylinder(h=100, r=1.1);
            }
            
            translate([-nose_cone_inner_diam / 2 + 2.5, 0, 4])
            rotate([0,-90,0])
            union() {
                NutM2();
                cylinder(h=100, r=1.1);
            }
        }
    }
    
    //base 
    difference() {
        cylinder(h=base_height, r=outer_diam/2);
        translate([-29/2,-10,3])
        camera_pcb_holes();
    }
    translate([-29/2,-10,3])
    camera_pcb();
}

module base_adapter() {
    outer_diam = 52.5;
    inner_diam = 48;
    inner_inner_diam = 46.5;
    difference() {
        cylinder(h=2, r=outer_diam/2);
        translate([-29/2,-10,3])
        camera_pcb_holes();
        
        translate([-29/2,-10,1])
        union() {
            distance = 25.5;
            translate([1.5,1.5,0])
            NutM2();
            
            translate([1.5 + distance,1.5,0])
            NutM2();
            
            translate([1.5 + distance, 1.5 + distance, 0])
            NutM2();
            
            translate([1.5,1.5 + distance,0])
            NutM2();
        }
    }
    
    translate([0,0,-30])
    difference() {
        cylinder(h=30, r = inner_diam/2);
        translate([0,0,-1])
        cylinder(h=31.01, r = inner_inner_diam/2);
    }
    
    translate([0,0,-10])
    difference() {
        translate([-2.5, -7.5, 0])
        cube([5,15,10]);
        translate([-3.5,-2.5,5])
        cube([7,5,5]);
    }
}


module nose_cone() {
    inner_diam = 50.75;
    outer_diam = 52.5;
    tube_length = 65;
    //nose
    difference() {
        translate([0, 0, tube_length])
        cone_elliptical(R=outer_diam/2, L=120, s=155);
        translate([0, 0, tube_length - 3])
        cone_elliptical(R=inner_diam/2, L=120, s=155);
    }
    
    //tube
    difference() {
        cylinder(tube_length + 1, outer_diam/2, outer_diam/2);
        translate([0,0,-1])
        cylinder(tube_length + 3, inner_diam/2, inner_diam/2);
        
        //vent hole
        translate([0,0,10])
        rotate([90,0,0])
        cylinder(200, 4, 4);
        
        //screw_holes
        translate([-100,0,3])
        rotate([0,90,0])
        cylinder(h=200, r=1.1);
        
        //camera hole
        translate([0,0,17])
        rotate([-90,0,0])
        cylinder(h = 200, r = 8);
    }
    
}

module camera_pcb() {
    distance = 25.5;
    /*
    rotate([0,0,0])
    color("blue")
    cube([29,29,5]);
    */
    
    translate([1.5,1.5,0])
    difference() {
        translate([0,0,-2])
        cylinder(h=2,r=1.6);
        translate([0,0,-15])
        cylinder(h=30, r=1.1);
    }
    
    translate([1.5 + distance,1.5,0])
    difference() {
        translate([0,0,-2])
        cylinder(h=2,r=1.6);
        translate([0,0,-15])
        cylinder(h=30, r=1.1);
    }
    
    translate([1.5 + distance, 1.5 + distance, 0])
    difference() {
        translate([0,0,-2])
        cylinder(h=2,r=1.6);
        translate([0,0,-15])
        cylinder(h=30, r=1.1);
    }
    
    translate([1.5,1.5 + distance, 0])
    difference() {
        translate([0,0,-2])
        cylinder(h=2,r=1.6);
        translate([0,0,-15])
        cylinder(h=30, r=1.1);
    }
}

module camera_pcb_holes() {
    distance = 25.5;
    translate([1.5,1.5,-30])
    cylinder(h=30, r=1.1);
    
    translate([1.5 + distance,1.5,-30])
    cylinder(h=30, r=1.1);
    
    translate([1.5 + distance, 1.5 + distance, -30])
    cylinder(h=30, r=1.1);
    
    translate([1.5,1.5 + distance,-30])
    cylinder(h=30, r=1.1);
}

module camera() {
    difference() {
        color("green")
        translate([-7,-8.2,0])
        cube([14,22,14]);
        
        translate([-40,0,7])
        rotate([0,90,0])
        cylinder(h = 100, r = 1.1);
    }
}


module camera_mount() {
    thickness = 5;
    width = 2;
    bridge_height = 8;
    actual_width = 32;
    translate([-actual_width / 2 - width,-thickness/2,0])
    difference() {
        cube([actual_width + width * 2,thickness, bridge_height+width]);
        translate([width,-1,-1])
        cube([actual_width, thickness + 2, bridge_height+1]);
    }
    
    translate([-7.5 - width, -thickness/2,bridge_height+width])
    difference() {
        cube([15 + 2 * width, thickness, 14 + width]);
        translate([width,-1,0])
        cube([15, 100, 14.2]);
        
        translate([-40, thickness/2, 7])
        rotate([0,90,0])
        cylinder(h=100, r=1.1);
    }
}

union() {
    //translate([0,10,11])
    //camera();
    //translate([0,0,-1])
    //base_adapter();
    fc_mount_v2();
    difference() {
        //translate([0,0,1])
        //nose_cone();
        //translate([0,-500,0])
        //cube(1000);
    }
    /*
    translate([-18,-14,7])
    color("yellow")
    flight_controller();
    */
}