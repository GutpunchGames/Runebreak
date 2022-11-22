function handleResponse(data) {
    console.log(`handleResponse: ${JSON.stringify(data)}`);
}

export default function doRegister(username, password) {
    // Simple POST request with a JSON body using fetch
    const requestOptions = {
        method: 'POST',
    };
    fetch('http://localhost:9000/', requestOptions)
        .then(response => response.json())
        .then(data => handleResponse(data));
}