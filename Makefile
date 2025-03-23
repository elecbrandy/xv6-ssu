IMAGE_NAME      = xv6
IMAGE_TAG       = 0.0
CONTAINER_NAME  = xv6_container

HOST_CODE_PATH = /home/dongwook/goinfre/xv6-ssu
CONTAINER_CODE_PATH = /root/xv6-ssu

# Docker image build
build:
	docker build -t $(IMAGE_NAME):$(IMAGE_TAG) .

# Docker container run && mounting host's directory
run:
	@if docker ps -a --format '{{.Names}}' | grep -q "^$(CONTAINER_NAME)$$"; then \
		echo "Container exists. Starting it..."; \
		docker start $(CONTAINER_NAME) && docker exec -it $(CONTAINER_NAME) bash; \
	else \
		docker run -it --userns=host --name $(CONTAINER_NAME) -v $(HOST_CODE_PATH):$(CONTAINER_CODE_PATH) $(IMAGE_NAME):$(IMAGE_TAG) bash; \
	fi

# Exec container's bash
exec:
	docker exec -it $(CONTAINER_NAME) bash

# Run xv6 inside the container using QEMU
qemu:
	docker exec -it $(CONTAINER_NAME) make -C $(CONTAINER_CODE_PATH)/templates/xv6_ssu_init qemu-nox

# Stop container
stop:
	docker stop $(CONTAINER_NAME)

# Remove container
rm:
	docker rm $(CONTAINER_NAME)

# Remove image
rmi:
	docker rmi $(IMAGE_NAME):$(IMAGE_TAG)

# Clean all (stop + remove container/image)
clean:
	make stop || true && make rm || true && make rmi || true
