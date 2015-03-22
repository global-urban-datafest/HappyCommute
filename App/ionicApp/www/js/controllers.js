function log(msg, id){
	var node = document.createElement("div");                 // Create a <li> node
	var textnode = document.createTextNode(msg);
	node.appendChild(textnode);
	document.getElementById(id).appendChild(node);
}

angular.module('HC.controllers', ['HC.services'])

.controller('AppCtrl', function($rootScope, $scope, $ionicModal, $timeout, bluetooth) {
		$scope.devicesaved = bluetooth.getAddress();
		$rootScope.$on('blueToothDevice.address.saved', function(){
			$scope.devicesaved = bluetooth.getAddress();
			console.log('EVENT: blueToothDevice.address.saved RECIEVED');
		});
  // Form data for the login modal
  $scope.loginData = {};

  // Create the login modal that we will use later
  $ionicModal.fromTemplateUrl('templates/login.html', {
    scope: $scope
  }).then(function(modal) {
    $scope.modal = modal;
  });

  // Triggered in the login modal to close it
  $scope.closeLogin = function() {
    $scope.modal.hide();
  };

  // Open the login modal
  $scope.login = function() {
    $scope.modal.show();
  };

  // Perform the login action when the user submits the login form
  $scope.doLogin = function() {
    console.log('Doing login', $scope.loginData);

    // Simulate a login delay. Remove this and replace with your login
    // code if using a login system
    $timeout(function() {
      $scope.closeLogin();
    }, 1000);
  };
})

.controller('SettingsCtrl', function($rootScope, $scope, bluetooth) {



		$scope.devices = [];
		$scope.currentDevice = bluetooth.getAddress();
		$scope.getDevices = function(){
			bluetooth.list().then(function(devices){
				$scope.devices = devices;
			},function(error){
				$scope.devices = error;
			});
		};

			$scope.saveAddress = function (address){
				log('Saving device: '+address, 'console');
				bluetooth.setAddress(address);
				log('Saved device: '+address, 'console');
				$rootScope.$broadcast('blueToothDevice.address.saved', function() {console.log('address Save Broadcasted')});
				$scope.currentDevice = bluetooth.getAddress();
			};
		$scope.$on('$ionicView.enter', function(){
			$scope.currentDevice = bluetooth.getAddress();
			console.log('currentDevice', $scope.currentDevice);
		})




})
/*
.controller('PlaylistCtrl', function($scope, $stateParams, colorFactory) {
})*/
	.controller('ColorCtrl', function($scope, colorFactory, bluetooth){
		$scope.rgb = {r:125,g:125,b:125};
		$scope.$watch('$scope.rgb', function(){
			console.dir($scope.rgb);
		});
		$scope.saveRGB = function(){
			log('rgb: '+$scope.rgb);
			colorFactory.save($scope.rgb);
		};

		$scope.sendMessage = function(){
			var address = bluetooth.getAddress();

			bluetooth.connect(address).then(function(){
				var c = $scope.rgb;
				var hexcolor = colorFactory.rgbToHex(c.r, c.g, c.b);
				log('Color: '+hexcolor, 'consoleColor');
				bluetooth.sendMessage(hexcolor).then(function(res){
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
	})
	.factory('colorFactory', function($q, $http, $rootScope){
		// source: http://www.sepiariver.ca/blog/modx-web/rgb-to-hex-color-converter-javascript/
		function toHex(r,g, b){
			var hex = []; //initialize hex variable
			var rgbValues = [r,g,b];
			for (i=0;i<rgbValues.length;i+=1) {
				var
					y = rgbValues[i],
					h1 = Math.floor(y/16),
					h2 = y%16,
					hexChar = "0123456789ABCDEF";
				hex[i] = hexChar[h1] + hexChar[h2];
			}

			hex = hex.join(''); //get rid of commas
			return ";" + hex; // ; for bluetooth serial spacer

		}

		return {
			save: function(color){
				var deferred = $q.defer();
				var hex = toHex(color.r, color.g, color.b);

					var obj = {};
				obj.color = hex;
				$http({
					url: 'color/',
					dataType: "json",
					method: "POST",
					headers: {
						"Content-Type": "application/x-www-form-urlencoded"

					},
					data: obj
				}).
					success(function(data, status, headers, config) {
						// this callback will be called asynchronously
						// when the response is available
						deferred.resolve(data);
					}).
					error(function(data, status, headers, config) {
						// called asynchronously if an error occurs
						// or server returns response with an error status.
						deferred.reject(data);
					});
				return deferred.promise;
			},
			rgbToHex : toHex

		}
	});
