var map = function(p){

  width = 500;
  height = 500;

  var blinky;
  var destination;
  var y = 0;

  p.setup = function() {
    var canvas = p.createCanvas(width, height);
    canvas.parent("PlayingField");
    blinky = new Robot(width/2, height/4, 0);
  }

  p.draw = function() {
    p.background(52);
    p.stroke(1);
    p.line()


    blinky.draw(Xvalue, Yvalue, Anglevalue);
    if(destination != null)
    destination.draw();
    /*
    xCross = Veriables.Xvalue + width/2;
    yCross = height - y;
    p.line(0,yCross,width,yCross);
    p.line(xCross,0,xCross,height);
    */
  }

  p.mouseClicked = function(){
    destination = new Object(p.mouseX,height-p.mouseY);
  }

  function Robot(_x,_y,_dir){
    this.x = _x;
    this.y = _y;
    this.dir = _dir;

    this.width = 30;
    this.height = 50;

    this.arrow = Arrow = new Arrow(this.x,this.y,this.dir,this.width);

    this.draw = function(_x,_y,_dir){
      p.push();
      this.x = _x;
      this.y = _y;
      this.dir = _dir;
      p.fill(255,0,0);
      p.stroke(0);
      p.translate(this.x + width/2, height - this.y );
      p.rotate(this.dir/180*p.PI);
      p.rect(0- this.width/2,0- this.height/2, this.width, this.height);
      p.fill(255);
      p.pop();

      this.arrow.update(this.x + width/2, height - this.y, this.dir, this.width/12);
    }
  }

  function Arrow(x,y,dir,length){
    this.x=x;
    this.y=y;
    this.length = length;
    this.angle = dir;
    this.update = function(x,y,dir,length) {
      this.x=x;
      this.y=y;
      this.length = length;
      this.angle = dir;
    p.push();
    p.translate(this.x,this.y);
    p.rotate(this.angle/180*p.PI-p.PI/2);
    p.fill(255);
    p.beginShape()
    p.noStroke();
    p.vertex(0,-this.length);
    p.vertex(5*this.length, -this.length);
    p.vertex(5*this.length, -3*this.length);
    p.vertex(9*this.length, 0);
    p.vertex(5*this.length, 3*this.length);
    p.vertex(5*this.length, this.length);
    p.vertex(0,this.length);
    p.endShape();
    p.pop();
    }
  }

  function Object(_x,_y){
    this.x = _x;
    this.y = _y;

    this.draw = function(){
      p.fill(0,0,255);
      p.ellipse(this.x,height-this.y, 10, 10);
    }
  }

}

var mapClass = new p5(map, 'PlayingField');
