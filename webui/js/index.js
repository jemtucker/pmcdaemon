var radioContent = [
    {station: "", text: "", image: "", url: ""}
];

var app = angular.module('pmcApp', []);

app.controller('pmcController', function($scope) {

    $scope.navItems = [
        {text: "About", content: []},
        {text: "Radio", content: radioContent}];

    $scope.activeNav = $scope.navItems[0];

    $scope.setNavActive = function(item) {
        $scope.activeNav = item;
    };

    $scope.isNavActive = function(item) {
        return item === $scope.activeNav;
    };
});