/**
 * Created by John on 08/03/15.
 */
angular.module('HC.services', [])
	.factory('bluetooth', function($q) {
		var address;
	var bluetoothSerial = cordova.require('com.megster.cordova.bluetoothserial.bluetoothSerial');


	return {
		setAddress: function(mac_address){
			address = mac_address;
		},
		getAddress: function(){
			return address;
		},
		connect: function(id){
			var deferred = $q.defer();
			bluetoothSerial.connect(id, deferred.resolve, deferred.reject);
			return deferred.promise;
		},
		disconnect: function(){
			var deferred = $q.defer();
			bluetoothSerial.disconnect(deferred.resolve, deferred.reject);
			return deferred.promise;
		},
		sendMessage: function(message) {
			var deferred = $q.defer();
			bluetoothSerial.write(message, function(res){
				console.dir(res);
				deferred.resolve(res);
			}, function(err){
				console.dir(err);
				deferred.reject(res);
			});
			return deferred.promise;
		},
		list :function(){
			var deferred = $q.defer();
			bluetoothSerial.list(/*function(devices){
				deferred.resolve(devices);

			}*/
				function(peripherals) {
				console.log(JSON.stringify(peripherals));
				// populate mac address for first device
				//connectText.value = peripherals[0].id;
					deferred.resolve(peripherals)
			}, function(error){
				deferred.reject(error);
			});

			return deferred.promise;

		}
	};
})

.factory('Socket', function($rootScope, bluetooth, colorFactory) {
	var service = {};
	var client = {};
	var topic = "testtopic";

	service.connect = function(host, port, user, password) {
		var options = {
			username: user,
			password: password
		};
		console.log("Try to connect to MQTT Broker " + host + " with user " + user);
		client = mqtt.createClient(parseInt(port),host,options);
		client.subscribe(topic+"/#");
		client.on('error', function(err) {
			console.log('error!', err);
			client.stream.end();
		});
		client.on('message', function (topic, message) {
			service.onMessage(topic, message);
		});
	}

	service.publish = function(payload) {
		client.publish(topic,payload, {retain: true});
		console.log('publish-Event sent '+ payload + ' with topic: ' + topic + ' ' + client);
	}

	service.onMessage = function(topic, message) {
		console.log('publish-Event received '+ message + ' with topic: ' + topic);
		var address = bluetooth.getAddress();

		if(address){
			bluetooth.connect(address).then(function(){
				bluetooth.sendMessage(message).then(function(res){
					log(res, 'consoleColor');
					bluetooth.disconnect().then(function(res){
						log(res, 'consoleColor');
					}, function(error){
						log('disconnect ERROR:'+error, 'consoleColor');
					})
				},function(error){
					log('sendMessage ERROR:'+error, 'consoleColor');
				});
			}, function(error){
				log('connect ERROR:'+error, 'consoleColor');
			});
		}

	};
	return service;
});

