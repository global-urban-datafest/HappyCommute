/**
 * Created by John on 08/03/15.
 */
angular.module('HC.services', [])
	.factory('bluetooth', function() {
	var bluetoothSerial = cordova.require('bluetoothSerial');

	return {
		sendMessage: function(message) {
			// interact with bluetoothSerial
		}
	};
});

