<<<<<<< HEAD
// This object contains a list of all the controls on the dashboard. If you add a new interactive element, you'll need to put it in this object.
var ui = {
	connection: document.getElementById('connection'),
	Xvalue: document.getElementById('X'),
	Yvalue: document.getElementById('Y'),
	Anglevalue: document.getElementById('Angle'),
	pistonButton: document.getElementById('pistonButton'),
	calibration: document.getElementById('calibration'),
	calibrateButton: document.getElementById('calibrateButton'),

	inputX:					document.getElementById('x-input'),
	inputY: 				document.getElementById('y-input'),
	inputAngle: 		document.getElementById('angle-input'),
	SendCordinate:	document.getElementById('SendCordinate')

};


var Xvalue = 0;
var Yvalue = 0;
var Anglevalue = 0;
var Calibrationvalue = 0;

var pistonvalue = false;
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
			case '/data/Position/X':
				Xvalue = value;
				ui.Xvalue.innerHTML = "X= " + Xvalue;
				break;
			case '/data/Position/Y':
				Yvalue = value;
				ui.Yvalue.innerHTML = "Y= " + Yvalue;
				break;
			case '/data/Position/Angle':
				Anglevalue = value;
				ui.Anglevalue.innerHTML = "Angle= " + Anglevalue;
				break;
			case '/data/Calibration':
				Calibrationvalue = value;
				ui.calibration.innerHTML = "Calibration value for Eduard is = " + Calibrationvalue;
				break;
	}
	// In the real dashboard, there will be more code here to manage the Tuning section of the UI.
	// That code is not included in this example because it's very confusing and you usually don't need to modify it anyway.
}

ui.pistonButton.onclick = function() {
	console.log("open pistion");
	NetworkTables.setValue('/data/pistons', true);
}

ui.calibrateButton.onclick = function() {
	console.log("calibarting")
	NetworkTables.setValue('/data/calibrating', true);
}

ui.SendCordinate.onclick = function(){
	NetworkTables.setValue('/data/Destination/X', ui.inputX.innerHTML);
	NetworkTables.setValue('/data/Destination/Y',ui.inputY.innerHTML);
	NetworkTables.setValue('/data/Destination/Angle',ui.inputAngle.innerHTML);
	//mapClass.destination.x = NetworkTables.setValue('/data/Position/X', ui.inputX.innerHTML);
	//mapClass.destination.y = NetworkTables.setValue('/data/Position/Y',ui.inputY.innerHTML);
	//mapClass.destination.dir = NetworkTables.setValue('/data/Position/Angle',ui.inputAngle.innerHTML);
}

// The folllowing functions are called when the user interacts with control elements.
/*
ui.light.onclick = function() {
	// Set NetworkTables value to the new checked state of the checkbox.
	NetworkTables.setValue('/SmartDashboard/light', ui.light.checked);
};

ui.winchMonitor.onclick = function() {
	console.log(NetworkTables.getValue('data/Jorn/Piet'));
	ui.winchMonitor.innerHTML = NetworkTables.isRobotConnected();
    // Set the winch's openness to the opposite of what it currently is.
    //NetworkTables.setValue('/SmartDashboard/winch', !NetworkTables.getValue('/SmartDashboard/winch'));
		//NetworkTables.setValue('/SmartDashboard/winch', NetworkTables.isRobotConnected());
};*/
=======
// This object contains a list of all the controls on the dashboard. If you add a new interactive element, you'll need to put it in this object.
var ui = {
	connection: document.getElementById('connection'),
	Xvalue: document.getElementById('X'),
	Yvalue: document.getElementById('Y'),
	Anglevalue: document.getElementById('Angle'),
	pistonButton: document.getElementById('pistonButton'),
	calibration: document.getElementById('calibration'),
	calibrateButton: document.getElementById('calibrateButton'),

	inputX:					document.getElementById('x-input'),
	inputY: 				document.getElementById('y-input'),
	inputAngle: 		document.getElementById('angle-input'),
	SendCordinate:	document.getElementById('SendCordinate')

};


var Xvalue = 0;
var Yvalue = 0;
var Anglevalue = 0;
var Calibrationvalue = 0;

var pistonvalue = false;
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
			case '/data/Position/X':
				Xvalue = value;
				ui.Xvalue.innerHTML = "X= " + Xvalue;
				break;
			case '/data/Position/Y':
				Yvalue = value;
				ui.Yvalue.innerHTML = "Y= " + Yvalue;
				break;
			case '/data/Position/Angle':
				Anglevalue = value;
				ui.Anglevalue.innerHTML = "Angle= " + Anglevalue;
				break;
			case '/data/Calibration':
				Calibrationvalue = value;
				ui.calibration.innerHTML = "Calibration value for Eduard is = " + Calibrationvalue;
				break;
	}
	// In the real dashboard, there will be more code here to manage the Tuning section of the UI.
	// That code is not included in this example because it's very confusing and you usually don't need to modify it anyway.
}

ui.pistonButton.onclick = function() {
	console.log("open pistion");
	NetworkTables.setValue('/data/pistons', true);
}

ui.calibrateButton.onclick = function() {
	console.log("calibarting")
	NetworkTables.setValue('/data/calibrating', true);
}

ui.SendCordinate.onclick = function(){
	/*
	NetworkTables.setValue('/data/Destination/X', ui.inputX.innerHTML);
	NetworkTables.setValue('/data/Destination/Y',ui.inputY.innerHTML);
	NetworkTables.setValue('/data/Destination/Angle',ui.inputAngle.innerHTML);*/
	//mapClass.destination.x = NetworkTables.setValue('/data/Position/X', ui.inputX.innerHTML);
	//mapClass.destination.y = NetworkTables.setValue('/data/Position/Y',ui.inputY.innerHTML);
	//mapClass.destination.dir = NetworkTables.setValue('/data/Position/Angle',ui.inputAngle.innerHTML);
}

// The folllowing functions are called when the user interacts with control elements.
/*
ui.light.onclick = function() {
	// Set NetworkTables value to the new checked state of the checkbox.
	NetworkTables.setValue('/SmartDashboard/light', ui.light.checked);
};

ui.winchMonitor.onclick = function() {
	console.log(NetworkTables.getValue('data/Jorn/Piet'));
	ui.winchMonitor.innerHTML = NetworkTables.isRobotConnected();
    // Set the winch's openness to the opposite of what it currently is.
    //NetworkTables.setValue('/SmartDashboard/winch', !NetworkTables.getValue('/SmartDashboard/winch'));
		//NetworkTables.setValue('/SmartDashboard/winch', NetworkTables.isRobotConnected());
};*/
>>>>>>> 4204f010ef2df5beffd6d1ab965234272a50f306
