var map = function(p){

  width = 750;
  height = 750;


  var blinky;
  var destination;
  var y = 0;

  p.setup = function() {
    var canvas = p.createCanvas(width, height);
    canvas.parent("PlayingField");
    //p.frameRate(1);
    blinky = new Robot(width/2, height/4, 0);
  }

  p.draw = function() {
    p.background(52);
    p.stroke(1);
    p.line()


    blinky.draw(Xvalue/2 + width/2, Yvalue/2 + height/2, Anglevalue);
    if(destination != null){
      destination.draw();
      //MoveBlinky();
    }
    /*
    xCross = Veriables.Xvalue + width/2;
    yCross = height - y;
    p.line(0,yCross,width,yCross);
    p.line(xCross,0,xCross,height);
    */
  }

  var index = 0;
  var angleToGo = 0;
  var distance = 0;
  var oldX = 0;
  var oldY = 0;
  var oldDir = 0;

  function MoveBlinky(){
    if(oldX != destination.x || oldY != destination.y)
      index = 0;



    switch(index){
      case 0: //calculate de veriables
        oldX = destination.x;
        oldY = destination.y;
        oldDir = (blinky.dir+360)%360;
        angleToGo = calcAngleToGo(destination.x,destination.y);
        distance = p.sqrt(p.pow(destination.x-blinky.x,2),p.pow(destination.y-blinky.y,2));

        index++;
        //no break because it needs to do this always just 1 time
      case 1://turn around
        if(blinky.turn(angleToGo)){
          index++;
        }
        break;
      case 2://move forward
        if(blinky.drive(distance)){
          oldDir = blinky.dir;
          index++;
        }
        break;
      case 3://turn to designated angle
        if(blinky.turn((destination.dir-oldDir+5*360)%360)){
          index++;
        }
        break;
    }
  }

  function calcAngleToGo(x,y){
    var dx = x-blinky.x;
    var dy = y-blinky.y;
    var angle = p.atan2(dy,dx)/p.PI*180*-1+90;//to degrees
    while(angle < 0){
      angle += 360;
    }
    angle = angle%360;
    return (angle - oldDir);
  }


  var oldmouseX;
  var oldmouseY;
  p.mousePressed = function(){
    oldmouseX = p.mouseX;
    oldmouseY = p.mouseY;
  }
  p.mouseReleased = function(){
    if( p.mouseX < 0 || p.mouseX > width ||
        p.mouseY < 0 || p.mouseY > height||
        oldmouseX < 0|| oldmouseX> width ||
        oldmouseY < 0|| oldmouseY> height)
        return;

    var dx = p.mouseX-oldmouseX;
    var dy = p.mouseY-oldmouseY;
    var mousedir = p.atan2(dy,dx)/p.PI*180+90;
    destination = new Object(oldmouseX,height-oldmouseY, mousedir);
  }



  function Robot(_x,_y,_dir){
    this.x = _x;
    this.y = _y;
    this.dir = _dir%360;

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
      var rotation = this.dir/180*p.PI;
      p.translate(this.x, height - this.y );
      p.rotate(rotation);
      p.rect(0- this.width/2,0- this.height/2, this.width, this.height);
      p.fill(255);
      p.pop();

      this.arrow.update(this.x, height - this.y, rotation, this.width/12);
    }

    var driveIndex = 0;
    var oldDistance = 0;
    var driven = 0;
    var startX = 0;
    var startY = 0;
    var finishx = 0;
    var finishy = 0;
    this.drive = function(_distance){
      if(_distance != oldDistance)
        driveIndex = 0;

      if(driveIndex == 0){
          driven = 0;

          startX = this.x;
          startY = this.y;

          finishx = destination.x;
          finishy = destination.y;

          driveIndex++;
        }
      else{
        driven++;
        var togo = _distance - driven;

        this.x = startX + (finishx-startX) * (driven/_distance);
        this.y = startY + (finishy-startY) * (driven/_distance);
        if(togo < 1 || driven > _distance){
          this.x = finishx;
          this.y = finishy;
          driveIndex = 0;

          return true;
        }
        else{
          return false;
        }
      }
      oldDistance = _distance;
    }



    this.turn = function(_angle){

      _angle = (_angle+360)%360;
      var angledestination = (oldDir + _angle + 360)%360;

      if( angledestination < ((this.dir+360)%360 + 1) && angledestination > ((this.dir+360)%360 - 1)){
        this.dir = angledestination;
        return true;
      }
      else if( _angle <= 180 && _angle > 0){
        this.dir++;
        return false;
      }
      else {
        this.dir--;
        return false;
      }
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
    p.rotate(this.angle-p.PI/2);
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

  function Object(_x,_y,_dir){
    this.x = _x;
    this.y = _y;
    this.dir=(_dir+360)%360;
    this.draw = function(){
      p.fill(0,0,255);
      p.ellipse(this.x,height-this.y, 10, 10);
    }
  }
}

var mapClass = new p5(map, 'PlayingField');
