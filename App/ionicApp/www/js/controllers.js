angular.module('HC.controllers', [])

.controller('AppCtrl', function($scope, $ionicModal, $timeout) {
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

.controller('SettingsCtrl', function($scope) {

})
/*
.controller('PlaylistCtrl', function($scope, $stateParams, colorFactory) {
})*/
	.controller('ColorCtrl', function($scope, colorFactory){
		$scope.rgb = {r:125,g:125,b:125};
		$scope.$watch('$scope.rgb', function(){
			console.dir($scope.rgb);
		});
		$scope.saveRGB = function(){
			console.log('rgb', $scope.rgb);
			colorFactory.save($scope.rgb);
		}
	})
	.factory('colorFactory', function($q, $http){

		function componentToHex(c) {
			var hex = c.toString(16);
			return hex.length == 1 ? "0" + hex : hex;
		}

		function rgbToHex(r, g, b) {
			return componentToHex(r) + componentToHex(g) + componentToHex(b);
		}

		return {
			save: function(color){
				console.log('color', color);
				var deferred = $q.defer();
				var hex = rgbToHex(color.r, color.g, color.b);
				console.log('hex', hex);
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
			}
		}
	});
