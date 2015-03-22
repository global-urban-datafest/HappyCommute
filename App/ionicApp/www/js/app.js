// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
// 'starter.controllers' is found in controllers.js
angular.module('HappyCommute', ['ionic', 'HC.directives', 'HC.controllers', 'HC.services'])

.run(function($ionicPlatform) {
  $ionicPlatform.ready(function() {

	  // For Dev
    if (!window.cordova) {
      window.cordova = {
	      require: function(plugin){

		      if(plugin === 'com.megster.cordova.bluetoothserial.bluetoothSerial'){
			      return {
				      connect: function(id, onSuccess, onError){
					      onSuccess('ok');
				      },
				      disconnect: function(onSuccess, onError){
					      onSuccess('disconnect');
				      },
				      sendMessage: function(message, onSuccess, onError){
					      onSuccess('ok');
				      },
				      list: function(onSuccess, onError){
					      onSuccess([{id:'123', name:'Device1', address:'1:2:3:4'},
						      {id:'ABC', name:'Device2', address:'A:B:C:D'}])
				      }
			      }
		      }

	      }
      }
    }
    if (window.StatusBar) {
      // org.apache.cordova.statusbar required
      StatusBar.styleDefault();
    }
  });
})

.config(function($stateProvider, $urlRouterProvider) {
  $stateProvider

  .state('app', {
    url: "/app",
    abstract: true,
    templateUrl: "templates/menu.html",
    controller: 'AppCtrl'
  })

  .state('app.search', {
    url: "/search",
    views: {
      'menuContent': {
        templateUrl: "templates/social.html"
      }
    }
  })

  .state('app.browse', {
    url: "/custommood",
    views: {
      'menuContent': {
        templateUrl: "templates/browse.html",
	      controller: 'ColorCtrl'
      }
    }
  })
    .state('app.playlists', {
      url: "/playlists",
      views: {
        'menuContent': {
          templateUrl: "templates/loading.html",
          controller: 'PlaylistsCtrl'
        }
      }
    })

  .state('app.settings', {
    url: "/settings",
    views: {
      'menuContent': {
        templateUrl: "templates/settings.html",
        controller: 'SettingsCtrl'
      }
    }
  });
  // if none of the above states are matched, use this as the fallback
  $urlRouterProvider.otherwise('/app/custommood');
});
