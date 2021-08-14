outer_diam = 18.25;
inner_diam = 15.5;
height = 8;

difference() {
    cylinder(h= height, r=outer_diam/2);
    translate([0,0,-1])
    cylinder(h= height + 2, r= inner_diam/2);
}
