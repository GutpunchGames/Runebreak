function handleResponse(data) {
    console.log(`handleResponse: ${JSON.stringify(data)}`);
}

export default function doUpdateUser(username, userId, token) {
    const requestOptions = {
        method: 'PATCH',
        headers: {'X-Auth-Token': token},
        body: JSON.stringify({username: username})
    };

    const url = `http://localhost:9000/accounts/${userId}`
    fetch(url, requestOptions)
        .then(response => response.json())
        .then(data => handleResponse(data));
}