#include <stdio.h>
void main()
{
    int incoming_packet_size, outgoing_packet_size;
    int current_bucket_size = 0, bucket_size;
    int overflow, current_outgoing_size, stop;

    printf("\nEnter the following details in order");
    printf("\n\t1 : Bucket Size");
    printf("\n\t2 : Outgoing Packet Size\n");
    scanf("%d", &bucket_size);
    scanf("%d", &outgoing_packet_size);

    while (1)
    {
        printf("\nEnter the incoming packet size\n(Enter -1 to stop)\n");
        scanf("%d", &incoming_packet_size);
        if (incoming_packet_size == -1)
        {
            break;
        }

        if(incoming_packet_size <= bucket_size)
        {
            current_bucket_size = current_bucket_size + incoming_packet_size;
            printf("\nBucket used %d out of %d", current_bucket_size, bucket_size);
        }
        else
        {
            printf("\nOverflow Occurred");
            overflow = incoming_packet_size - (bucket_size - current_bucket_size);
            printf("\nDropped %d packets", overflow);
        }

        current_outgoing_size = outgoing_packet_size;
        if(current_outgoing_size > current_bucket_size)
        {

            current_outgoing_size = (current_bucket_size - current_outgoing_size) + outgoing_packet_size;
        }

        printf("\nPackets Outgoing %d out of %d", current_outgoing_size, current_bucket_size);
        
        current_bucket_size = current_bucket_size - current_outgoing_size;
        printf("\nBucket used %d out of %d\n", current_bucket_size, bucket_size);

    }
    printf("\n\nHAVE A WONDERFUL DAY!!!\n\n");
}