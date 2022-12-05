#!/bin/sh

echo "Connecting to default vm instance-1 in GCP using ssh..."

EXTERNAL_IP="34.105.24.189"

ssh -i ~/.ssh/google_cloud_key $USER@$EXTERNAL_IP
