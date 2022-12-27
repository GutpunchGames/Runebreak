function handleResponse(data) {
    console.log(`handleResponse: ${JSON.stringify(data)}`);
}

export default function doSendMessage(recipientId, text, token) {
    console.log(`doSendMessage: ${recipientId} -- ${text} -- ${token}`)
    const requestOptions = {
        method: 'POST',
        headers: {'X-Auth-Token': token},
        body: JSON.stringify({recipientId: recipientId, text: text})
    };

    console.log(`body: ${requestOptions.body}`)

    const url = `http://localhost:9000/messages`
    fetch(url, requestOptions)
        // .then(response => response.json())
        // .then(data => handleResponse(data));
}