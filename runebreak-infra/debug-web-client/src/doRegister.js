function handleResponse(data) {
    console.log(`handleResponse: ${JSON.stringify(data)}`);
}

export default function doRegister(username, password) {
    // Simple POST request with a JSON body using fetch
    const requestOptions = {
        method: 'POST',
        body: JSON.stringify({username:username, password:password})
    };
    fetch('http://localhost:9000/register', requestOptions)
        .then(response => response.json())
        .then(data => handleResponse(data));
}