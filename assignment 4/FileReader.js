//  Create an HTML button with a relevant ID in  your html file
<div>
<input type="file" id="file-input"/>
</div>

// Within your JS file, have an event listener that will call the function 
// readSingleFile with an argument of the event that it receives
document.getElementById('file-input').addEventListener('change', 
        readSingleFile, false);

// The following function will read the data which you are required to parse 
// accordingly 
function readSingleFile(e) {
    var file = e.target.files[0];
    if (!file) {
	return;
    }
    // Initialize file reader
    var reader = new FileReader();
    reader.onload = function(e) 
    {
        var contents = e.target.result.split("\n");
        // Process your lines over here.
        // console.log(contents[0]) should give you ply (the first line)
    };
    reader.readAsText(file);
}
