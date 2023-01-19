package connections

type WSMessage struct {
	MessageType string `json:"messageType"`
	Payload     string `json:"payload"`
}