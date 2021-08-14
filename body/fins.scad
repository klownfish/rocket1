$fn = 250;
base = 40;
length = 60;
thickness = 1.5;

scale([base/2,length,1])
difference() {
    cylinder(h=thickness, r=1);
    translate([-25,0,-1])
    cube([50,50,50]);
}