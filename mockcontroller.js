app.connect = function() {

	var IPAddress = $('#IPAddress').val()
	console.log('Trying to connect to ' + IPAddress)

	$('#startView').hide()
	$('#connectingStatus').text('Connecting to ' + IPAddress)
	$('#connectingView').show()

	chrome.sockets.tcp.create(function(createInfo) {

		app.socketId = createInfo.socketId

		chrome.sockets.tcp.connect(
			app.socketId,
			IPAddress,
			app.PORT,
			connectedCallback)
	})

	function connectedCallback(result) {
	
		if (result === 0) {

			 console.log('Connected to ' + IPAddress)
			 $('#connectingView').hide()
			 $('#controlView').show()
		}
		else {

			var errorMessage = 'Failed to connect to ' + app.IPAdress
			console.log(errorMessage)
			navigator.notification.alert(errorMessage, function() {})
			$('#connectingView').hide()
			$('#startView').show()
		}
	}
}

app.waterPlant = function() {
	app.sendString('W')
}

app.readMoisture = function() {
	app.sendString('R')
}

app.disconnect = function() {

	chrome.sockets.tcp.close(app.socketId, function() {
		console.log('TCP Socket close finished.')
	})
	$('#controlView').hide()
	$('#startView').show()
}
