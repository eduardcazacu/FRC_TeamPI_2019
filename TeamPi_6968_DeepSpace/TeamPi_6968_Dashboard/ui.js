

// This object contains a list of all the controls on the dashboard. If you add a new interactive element, you'll need to put it in this object.
var ui = {
	connection: document.getElementById('connection'),
	//Xvalue: document.getElementById('X'),
	//Yvalue: document.getElementById('Y'),
	//Anglevalue: document.getElementById('Angle'),
	x0: 30,
	y0: 30,
	x1: 40,
	y1: 40,

	Tolerance: document.getElementById('Tolerance')
};

	Angle = document.getElementById("Angle PID").querySelectorAll(".slider"),
	Distance = document.getElementById("Distance").querySelectorAll(".slider"),
	DistAngle = document.getElementById("Distance Angle").querySelectorAll(".slider")



for(var i = 0; i<5;i++){
	Angle[i].oninput = function(){
		var key = '/data/PID/Angle/'+this.id;
		NetworkTables.setValue(key, this.value);
	}
}
for(var i = 0; i<5;i++){
	Distance[i].oninput = function(){
		NetworkTables.setValue('/data/PID/Distance/'+this.id, this.value);
	}
}
for(var i = 0; i<5;i++){
	DistAngle[i].oninput = function(){
		NetworkTables.setValue('/data/PID/DistAngle/'+this.id, this.value);
	}
}

Tolerance.oninput = function(){
	NetworkTables.setValue('/data/PID/Tolerance'), this.val
}


var Xvalue = 0;
var Yvalue = 0;
var Anglevalue = 0;

// Sets function to be called on NetworkTables connect. Commented out because it's usually not necessary.
// NetworkTables.addWsConnectionListener(onNetworkTablesConnection, true);

// Sets function to be called when robot dis/connects. Commented out because it's not an essential thing to learn and you usually won't need to touch it.
//NetworkTables.addRobotConnectionListener(onRobotConnection, true);
NetworkTables.addRobotConnectionListener(function(connected){
	ui.connection.innerHTML = connected ? "Connected" : "No connection";
    console.log("Robot connected: " + connected);
}, true);


// Sets function to be called when any NetworkTables key/value changes
NetworkTables.addGlobalListener(onValueChanged, true);



/**
 *  @param key {string} The name of the variable.
 *  @param value {*} The value of the variable.
 *  @param isNew {boolean} Has the value not yet been passed to this instance of the Dashboard?
 */
function onValueChanged(key, value, isNew) {
	// Sometimes, NetworkTables will pass booleans as strings. This corrects for that. You probably shouldn't have to touch this code.
	if (value == 'true') {
		value = true;
	} else if (value == 'false') {
		value = false;
	}

	// This switch statement chooses which UI element to update when a NetworkTables variable changes.
	// So, if the robot changes the value of a NetworkTables variable, the state of a control will change.
	switch (key) {/*
		case '/SmartDashboard/light':
			// Set the checkedness of this control element.
			ui.light.checked = value;
            break;
      case '/SmartDashboard/winch':
          // If you haven't seen the thing at the end of this line, it's basically just a compact switch statement with a boolean.
          ui.winchMonitor.innerHTML = value ? 'Winch open' : 'Winch closed';
          // If you made it a real if statement, it would look something like this:
          /*
          if (value) {
              ui.winchMonitor.innerHTML = 'Winch open';
          } else {
              ui.winchMonitor.innerHTML = 'Winch closed';
          }
          */
          // As you can see, it's better if you do it this short way. For more help, see https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Conditional_Operator
          //break;
			case '/data/position/x':
				Xvalue = value;
				ui.Xvalue.innerHTML = "X= " + Xvalue;
				break;
			//case '/data/position/y':
			case 'test':
				Yvalue = value;
				ui.Yvalue.innerHTML = "Y= " + Yvalue;
				break;
			case '/data/position/r':
				Anglevalue = value;
				ui.Anglevalue.innerHTML = "Angle= " + Anglevalue;
				break;

			case '/data/pixy/x0':
				  x0 = value;
				  break;
			case '/data/pixy/y0':
				  y0 = value;
				  break;
			case '/data/pixy/x1':
				x1 = value;
				break;
			case '/data/pixy/y1':
				y1 = value;
				break;
	}
	// In the real dashboard, there will be more code here to manage the Tuning section of the UI.
	// That code is not included in this example because it's very confusing and you usually don't need to modify it anyway.
}

/*
ui.Tolerance.oninput = function(){
	NetworkTables.setValue('/data/testNick', ui.Tolerance.value);
}*/

/*
NetworkTables.addKeyListener('/SmartDashboard/drive/navx/yaw', (key, value) => {
    ui.gyro.val = value;
    ui.gyro.visualVal = Math.floor(ui.gyro.val - ui.gyro.offset);
    if (ui.gyro.visualVal < 0) { // Corrects for negative values
        ui.gyro.visualVal += 360;
    }
    ui.gyro.arm.style.transform = ('rotate(' + ui.gyro.visualVal + 'deg)');
    ui.gyro.number.innerHTML = ui.gyro.visualVal + 'º';
});
*/


/*
test.type = "range";
test.min = "-200";
test.max = "200";
test.value = "0";
test.class="slider";
test.id = "testid";*/




