// Copyright (c) 2024 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qml/models/snapshotqml.h>

#include <interfaces/node.h>
#include <node/context.h>
#include <node/utxo_snapshot.h>
#include <clientversion.h>
#include <validation.h>
#include <util/fs.h>
#include <util/fs_helpers.h>

SnapshotQml::SnapshotQml(interfaces::Node& node, QString path)
    : m_node(node), m_path(path) {}

    bool SnapshotQml::processPath()
    {
        ChainstateManager& chainman = *m_node.context()->chainman;
        const fs::path snapshot_path = fs::u8path(m_path.toStdString());
        if (!fs::exists(snapshot_path)) {
            return false;
        }

        FILE* snapshot_file{fsbridge::fopen(snapshot_path, "rb")};
        AutoFile coins_file{snapshot_file};
        if (coins_file.IsNull()) {
            return false;
        }

        node::SnapshotMetadata metadata{chainman.GetParams().MessageStart()};
        try {
            coins_file >> metadata;
        } catch (const std::exception& e) {
            return false;
        }

        bool result = m_node.loadSnapshot(coins_file, metadata, false);
        if (!result) {
            return false;
        }

        return true;
    }