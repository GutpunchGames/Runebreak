import LoginForm from './LoginForm'
import RegisterForm from './RegisterForm'
import './App.css';
import React from 'react';
import doRegister from './doRegister';
import doLogin from './doLogin';
import doAttemptConnect from './doAttemptConnect';
import AttemptConnectForm from './AttemptConnectForm';
import SendMessageForm from './SendMessageForm';
import doSendMessage from './doSendMessage';

function App() {

  const onSubmitRegister = (username, password) => {
    doRegister(username, password);
  };

  const onSubmitLogin = (username, password) => {
    doLogin(username, password);
  };

  const onSubmitDoConnect = (userId) => {
    doAttemptConnect(userId, "1234");
  };

  const onSubmitSendMessage = (recipientId, text) => {
    doSendMessage(recipientId, text, "debug-auth-token");
  };

  return (
    <div className="App">
      Register
      <br/>
      <RegisterForm onSubmit={onSubmitRegister} usernameLabel={'Username'} passwordLabel={'Password'}/>
      <br/>
      Log In
      <br/>
      <LoginForm onSubmit={onSubmitLogin} usernameLabel={'Username'} passwordLabel={'Password'}/>
      <br/>
      Connect to WebSocket
      <br/>
      <AttemptConnectForm onSubmit={onSubmitDoConnect} />
      <br/>
      Send Message
      <br/>
      <SendMessageForm onSubmit={onSubmitSendMessage} />
    </div>
  );
}

export default App;