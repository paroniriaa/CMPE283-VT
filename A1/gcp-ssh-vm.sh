#!/bin/sh

echo "Connecting to default vm instance-1 in GCP using ssh..."

USER={{Junjie}}

EXTERNAL_IP={{35.185.231.89}}

ssh-i ~/.ssh/google_cloud_key $USER@$EXTERNAL_IP
