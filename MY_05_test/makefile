server:
	g++ util.cpp address.cpp socket.cpp client.cpp -o client && \
	g++ util.cpp server.cpp epoll.cpp address.cpp socket.cpp channel.cpp -o server
clean:
	rm server && rm client