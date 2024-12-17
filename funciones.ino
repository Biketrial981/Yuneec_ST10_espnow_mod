void registrar_clientes() {
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // register second peer  
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  /// register third peer
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  /// register 4 peer
  memcpy(peerInfo.peer_addr, broadcastAddress4, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }    
}

void pines() {
  pinMode(2,INPUT_PULLUP);  //CH1 Y
  pinMode(3,INPUT_PULLUP);  //CH2 X
  pinMode(0,INPUT_PULLUP);  //CH4 Y DER
  pinMode(1,INPUT_PULLUP);  //CH5 X DER
  pinMode(4,INPUT_PULLUP);  // TILT CAMERA POT
  pinMode(5,INPUT_PULLUP);  // TORTUGA POT. TORTUGA=1, CONEJO=0
  pinMode(8,INPUT_PULLUP);  // PHOTO BUTTON
  pinMode(9,INPUT_PULLUP);  // VIDEO BUTTON
  //pinMode(21,INPUT_PULLUP);
  //pinMode(22,INPUT_PULLUP);
  //pinMode(23,INPUT_PULLUP); 
}