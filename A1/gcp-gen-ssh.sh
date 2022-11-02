#!/bin/sh

echo "Connecting to default SSH keys using ssh-keygen..."

USER={{Junjie}}

ssh-keygen -t rsa -f ~/.ssh/google_cloud_key -C $USER

cat /home/$USER/.ssh/my_google_cloud_key.pub

