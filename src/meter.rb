require 'byebug'
require 'rest-client'
require 'aws'

TABLE_NAME="hackday-2014-team43"
class Meter
  attr_accessor :table

  def initialize
    puts "Setting up DynamoDB"
    ddb = AWS::DynamoDB.new(access_key_id: ENV['KEY_ID'],
                            secret_access_key: ENV['ACCESS_KEY'])

    unless ddb.tables[TABLE_NAME].exists?
      @table = ddb.tables.create(TABLE_NAME, 1, 1)
      sleep 1 while table.status == :creating
      puts "Table #{TABLE_NAME} created"
    else
      puts "Table #{TABLE_NAME} already exists"
      @table = ddb.tables[TABLE_NAME]
    end
  end

  def poll
    table.load_schema

    begin
      light = JSON.parse(RestClient.get("https://api.spark.io/v1/devices/53ff71066667574810182167/light?access_token=770f6827b00fb9fcd0fd1fb39877787af4cdb001"))
      doc = JSON.parse(light["result"])
      doc = doc.merge(time: Time.now.to_i, device_id: light["coreInfo"]["deviceID"])

      puts "Uploading #{doc}"
      table.items.create(doc)

      sleep(5)
    end while true
  end
end

Meter.new.poll
