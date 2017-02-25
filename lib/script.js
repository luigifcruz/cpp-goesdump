var hostname = "";
var scrolled = false;

var DecoderFastCache = {
    signalQuality: 0
};
var DecoderCompleteCache = {};
var ConsoleCache = [];
var FilesCache = {};
var connected = false;

document.addEventListener('DOMContentLoaded', function() {
    // Get the Hostname and Port.
    hostname = window.location.href.split("/");
    hostname = hostname[0] + "//" + hostname[2];

    // Initial Fetch.
    updateDecoderFast();
    updateDecoderComplete();
    updateConsole();
    updateFiles();
    
    // Set Update Routines.
    setInterval(function(){ updateDecoderFast(); }, 500);
    setInterval(function(){ updateDecoderComplete(); }, 5000);
    setInterval(function(){ updateConsole(); }, 5500);
    setInterval(function(){ updateFiles(); }, 15000);

    // Setup Interations.
    $(".Console").on('scroll', function(){
        if($(this).scrollTop() + $(this).innerHeight() >= $(this)[0].scrollHeight-10) {
            scrolled = false;
            console.log("Set to false.");
        } else {
            scrolled = true;
            console.log("Set to true.");
        }
    });
}, false);

function updateDecoderFast() {
    $.ajax({
        url: hostname + '/data/fast',
        dataType: 'application/json',
        complete: function(data) {
            if (data.status == 200) {
                DecoderFastCache = JSON.parse(data.responseText);
            }
        }
    });
    updateDOM(1);
}

function updateDecoderComplete() {
    $.ajax({
        url: hostname + '/data/complete',
        dataType: 'application/json',
        complete: function(data) {
            if (data.status == 200) {
                DecoderCompleteCache = JSON.parse(data.responseText);
            }
        }
    });
    updateDOM(2);
}

function updateFiles() {
    $.ajax({
        url: hostname + '/data/files',
        dataType: 'application/json',
        complete: function(data) {
            if (data.status == 200) {
                FilesCache = JSON.parse(data.responseText).Files;
            }
        }
    });
    updateDOM(3);
}

function updateConsole() {
    $.ajax({
        url: hostname + '/data/console',
        dataType: 'application/json',
        complete: function(data) {
            if (data.status == 200) {
                updateDOMConsole(JSON.parse(data.responseText).Console);
            }
        }
    });
}

function updateDOMConsole(FetchObjects) {
    if (FetchObjects == "") return;
    FetchObjects.forEach(function(objectFetch) {
        var itensFound = 0;
        ConsoleCache.forEach(function(objectLocal) {
            if(objectFetch.text == objectLocal.text) {
                itensFound++;
            }
        });
        if(itensFound == 0) {
            ConsoleCache.push(objectFetch);
            $( ".Console" ).append( "<div id='C" + objectFetch.color + "' class='ConsoleLine'>" + objectFetch.text + "</div>" );
            if(!scrolled){
                $(".Console").animate({ scrollTop: $('.Console').prop("scrollHeight")}, 100);
            }
        }
    });
}

function updateDOM(field) {
    switch(field) {
        case 1:
            $( "#SignalQuality" ).text(DecoderFastCache.signalQuality + "%");
            $( "#FrameLock" ).css({ 'color': DecoderFastCache.frameLock == 1 ? 'green' : 'red' });
        break;
    }
}