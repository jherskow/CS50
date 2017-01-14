<?php if ($info["empty"] == false): ?>

<table>
    <thead>
        <td>--------Time--------</td>
        <td>--------Type--------</td>
        <td>--------Price---------</td>
        <td>--------Symbol----------</td>
        <td>--------Shares--------</td>
    </thead>
    
    <?php foreach ($history as $history_item): ?>
    
        <tr>
            <td><?= $history_item["time"] ?></td>
            <td><?= $history_item["type"] ?></td>
            <td><?= number_format($history_item["price"] , 2) ?></td>
            <td><?= strtoupper($history_item["symbol"]) ?></td>
            <td><?= $history_item["shares"] ?></td>
        </tr>
    
    <?php endforeach ?>
</table>

<?php else: ?>

<h2> You ain't got no history! </h2>



<?php endif ?>
    

<h2> Available Cash: <?=number_format($info["cash"] , 2)?>$ </h2>
