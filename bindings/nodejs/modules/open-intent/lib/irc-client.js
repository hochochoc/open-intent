
var SESSION_ID = '12345';

module.exports = function(uri, stdio) {
    return new IRCClient(uri, stdio);
}

function IRCClient(uri, stdio) {
    var readline = require('readline');
    var RestChatbotClient = require('./rest-client');

    var chatbotClient = new RestChatbotClient(uri);

    var rl = readline.createInterface({
        input: stdio.stdin,
        output: stdio.stdout,
        prompt: '> '
    });

    rl.prompt();

    rl.on('line', function(line) {
        if(line == 'quit') {
            process.exit();
        }

        chatbotClient.talk(SESSION_ID, line)
        .then(function(replies) {
            var output = '';
            for(var i in replies) {
                output += replies[i] + '\n';
            }
            stdio.stdout.write(output);
            rl.prompt();
        })
        .fail(function(response) {
            console.error(JSON.parse(response.body).message);
            rl.prompt();
        });
    });
}
