server:	
	g++ util.cpp socket.cpp  address.cpp client.cpp -o client && \
	g++ util.cpp socket.cpp epoll.cpp address.cpp server.cpp -o server
clean:
	rm server && rm client