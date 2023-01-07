package connections

import "github.com/GutpunchGames/Runebreak/runebreak-infra/protos/gateway"

type WSMessageType int32

const (
	MessageCreate WSMessageType = WSMessageType(gateway.Type_MESSAGE_CREATE)
	LobbyUpdate   WSMessageType = WSMessageType(gateway.Type_LOBBY_UPDATE)
)