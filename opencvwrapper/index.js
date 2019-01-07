var bindings = require('bindings');
var addon = bindings('opencvwrapper');

module.exports = function(){
	return new addon.OpenCvManager();
};