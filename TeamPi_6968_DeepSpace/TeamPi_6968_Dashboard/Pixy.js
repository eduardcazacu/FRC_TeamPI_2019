var pixyClass = function(p){

    width = 750;
    height = 750;

    p.setup = function(){
        var canvas = p.createCanvas(width, height);
        canvas.parent("Pixy");

    }

    p.draw = function(){
        p.background(52);
        p.stroke(255);
        p.strokeWeight(3);
        p.line(ui.x0*10,ui.y0*10,ui.x1*10,ui.y1*10);
    }


}

var pixyClass = new p5(pixyClass, 'Pixy');