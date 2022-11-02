#!/bin/sh

echo "creating default vm instance-1 in GCP using gcloud..."

#gcloud auth login --no-browser

gcloud auth login

gcloud config set project cmpe-283-367403

gcloud compute instances create instance-1 --project=cmpe-283-367403 --zone=us-west1-a --machine-type=n2-standard-2 --network-interface=network-tier=PREMIUM --maintenance-policy=MIGRATE --provisioning-model=STANDARD --service-account=558940717781-compute@developer.gserviceaccount.com --scopes=https://www.googleapis.com/auth/devstorage.read_only,https://www.googleapis.com/auth/logging.write,https://www.googleapis.com/auth/monitoring.write,https://www.googleapis.com/auth/servicecontrol,https://www.googleapis.com/auth/service.management.readonly,https://www.googleapis.com/auth/trace.append --tags=http-server,https-server --create-disk=auto-delete=yes,boot=yes,device-name=instance-1,image=projects/ubuntu-os-cloud/global/images/ubuntu-2204-jammy-v20221018,mode=rw,size=10,type=projects/cmpe-283-367403/zones/us-west1-a/diskTypes/pd-ssd --no-shielded-secure-boot --shielded-vtpm --shielded-integrity-monitoring --reservation-affinity=any --enable-nested-virtualization --min-cpu-platform="Intel Cascade Lake"

