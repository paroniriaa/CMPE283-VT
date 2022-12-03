#!/bin/sh

echo "creating inner vm 'ubuntu-vm' in KVM using virt..."

os="--os-type=linux"
cdrom="--cdrom=/var/lib/libvirt/images/ubuntu-22.04.1-desktop-amd64.iso"
vcpu="--vcpus=4"
ram="--ram=4096"
name="--name=ubuntu-vm"
disk="--disk=~/inner-vm, size=32"
type="--virt-type=kvm"
network="--network=default"
graphics="--graphics=none"

virt-install $name $os $disk $cdrom $cpu $ram $type $disk $graphics $network 
