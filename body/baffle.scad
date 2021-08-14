$fn = 250;


inner_diam = 49.5;
tube_length = 50;
holes_offset = 25;

difference() {
    union() {
        //lower plate
        cylinder(h=1, r=inner_diam/2);
        //hole
        cylinder(h=tube_length, r=inner_diam/4 + 2.5);
        
        //supports
        holders = 16;
        for (i = [1:1:holders]) {
            translate([0,0,1])
            rotate([0,0,360/holders * i])
            translate([inner_diam/4 + 0.5,0,0])
            rotate([90,0,0])
            translate([0,0,-0.5])
            linear_extrude(1)
            polygon(points = [[0,0], [11.5, 0], [0, 15]]);
        }
    }
    translate([0,0,-2])
    cylinder(h=tube_length, r=inner_diam/4);
    
    //holes
    holes = 7;
    for (i = [1:1:holes]) {
        translate([0,0,holes_offset])
        rotate([0,0,360/holes * i])
        rotate([0,90,0])
        cylinder(h=100, r =5);
        
        translate([0,0,holes_offset + 15])
        rotate([0,0,360/holes * i])
        rotate([0,90,0])
        cylinder(h=100, r =5);
    }
}

//upper plate
difference() {
    translate([0,0,tube_length])
    cylinder(h=2.5, r=inner_diam/2);
    holes=8;
    for (i = [1:1:holes]) {
        translate([0,0,holes_offset])
        rotate([0,0,360/holes * i])
        translate([19,0,0])
        cylinder(h=100, r =4);
    }
}