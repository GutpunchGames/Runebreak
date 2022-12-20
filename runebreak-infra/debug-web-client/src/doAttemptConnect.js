export default function doAttemptConnect(userId, token) {
    const url = `ws://localhost:9000/connect/${userId}`
    const ws = new WebSocket(url);

    ws.onopen = (event) => {
        console.log('websocket opened');
    }
}