// import (
// 	"context"
// 	"fmt"
// 	"log"
// 	"net/http"
// 	"os"
// 	"os/signal"
// 	"time"

// 	"github.com/AndyG/GoMicroservicesTutorial/handlers"
// 	"github.com/gorilla/mux"
// 	"google.golang.org/grpc"
// )

// func main() {
// 	logger := log.New(os.Stdout, "prod-api-service", log.LstdFlags)

// 	productsHandler := handlers.NewProducts(logger)

// 	serveMux := mux.NewRouter()
// 	getRouter := serveMux.Methods(http.MethodGet).Subrouter()
// 	getRouter.HandleFunc("/", productsHandler.GetProducts)
// 	putRouter := serveMux.Methods(http.MethodPut).Subrouter()
// 	putRouter.HandleFunc("/{id:[0-9]+}", productsHandler.UpdateProduct)
// 	putRouter.Use(productsHandler.AddMiddlewareProductValidation)
// 	postRouter := serveMux.Methods(http.MethodPost).Subrouter()
// 	postRouter.HandleFunc("/", productsHandler.AddProduct)
// 	postRouter.Use(productsHandler.AddMiddlewareProductValidation)

// 	conn, err := grpc.Dial("localhost:9092", grpc.WithInsecure())
// 	if err != nil {
// 		panic(err)
// 	}
// 	defer conn.Close()

// 	currencyClient := protos.NewCurrencyClient(conn)

// 	// type CurrencyClient interface {
// 	// 	GetRate(ctx context.Context, in *RateRequest, opts ...grpc.CallOption) (*RateResponse, error)
// 	// }

// 	// type RateRequest struct {
// 	// 	state         protoimpl.MessageState
// 	// 	sizeCache     protoimpl.SizeCache
// 	// 	unknownFields protoimpl.UnknownFields

// 	// 	Base        Currencies `protobuf:"varint,1,opt,name=Base,proto3,enum=Currencies" json:"Base,omitempty"`
// 	// 	Destination Currencies `protobuf:"varint,2,opt,name=Destination,proto3,enum=Currencies" json:"Destination,omitempty"`
// 	// }

// 	rr := protos.RateRequest{Base: protos.Currencies_USD, Destination: protos.Currencies_EUR}
// 	fmt.Printf("created rr: %s", rr)
// 	res, err := currencyClient.GetRate(context.TODO(), &rr)
// 	fmt.Printf("got response: %s", res)

// 	server := &http.Server{
// 		Addr: "localhost:9090",
// 		Handler: serveMux,
// 		IdleTimeout: 120 * time.Second,
// 		ReadTimeout: 1 * time.Second,
// 		WriteTimeout: 1 * time.Second,
// 	}

// 	go func() {
// 		err := server.ListenAndServe()
// 		if err != nil {
// 			logger.Fatalf("error: %s", err)
// 		}
// 	}()

// 	sigChan := make(chan os.Signal)
// 	signal.Notify(sigChan, os.Interrupt)
// 	signal.Notify(sigChan, os.Kill)

// 	sig := <- sigChan
// 	logger.Println("Received terminate, graceful shutdown", sig)

// 	tc, cancelFunc := context.WithTimeout(context.Background(), 30 * time.Second)
// 	server.Shutdown(tc)
// 	cancelFunc()
// }