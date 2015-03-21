angular.module('HC.directives', [])
	.directive('colorviewer', function ($rootScope) {
		return {
			scope:{
				hex: '=',
				r: '=',
				g: '=',
				b: '='
			},
			restrict: 'E',
			link: function (scope, elem, attrs) {
				function setColor() {
					console.log('r', scope.r);
					console.log('g', scope.g);
					console.log('b', scope.b);
					var color = "red";
					//elem.css({"background-color":color});
					elem.css({"background-color": "rgb(" + scope.r + ", " + scope.g + ", " + scope.b + ")"});
				}
				setColor();
				//$rootScope.$on(attrs.r, setColor);
				scope.$watch('r', setColor)
				scope.$watch('g', setColor)
				scope.$watch('b', setColor)
			}
		}
	});;
